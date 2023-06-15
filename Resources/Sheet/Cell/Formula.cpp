#include "Formula.h"
#include "../Sheet.h"
#include "FormulaCell.h"
#include "../Misc/Misc.h"

Formula::Formula(Sheet* sheet, const Address& address, const std::string& expression) : sheet(sheet), address(address), expression(expression)
{
	Parse();
}

void Formula::Parse(bool removeDependencies)
{
	valid = true;
	errorMessage = "";
	std::string formula = expression;
	formula.erase(formula.begin());
	formula = Misc::Trim(formula);

	value = Compute(formula, removeDependencies);
}

const std::variant<std::monostate, std::string, double>& Formula::Value() const
{
	return value;
}

std::variant<std::monostate, std::string, double> Formula::Compute(const std::string& term, bool removeDependencies)
{
    std::string input = term;
	std::variant<std::monostate, std::string, double> result;

	if (IsString(input))
	{
		input.erase(input.begin());
		input.erase(input.end() - 1);
		return input;
	}

	double number{ 0 };
	if (IsNumber(input, number))
	{
		return number;
	}

	if (IsReference(input))
	{
		return ComputeReference(input, removeDependencies);
	}

	int paramsStart = static_cast<int>(input.find_first_of('('));

	if (paramsStart <= 0 || input.back() != ')') 
	{ 
		return Invalid("Invalid syntax!");
	}

	std::string formula = input.substr(0, paramsStart);
	formula = Misc::Trim(formula);

    std::string paramsText = input.substr((paramsStart + 1), input.size());
    paramsText.pop_back();
	paramsText = Misc::Trim(paramsText);

    std::vector<std::string> params = SplitParameters(paramsText);

	if (params.empty()) 
	{ 
		return Invalid("Invalid syntax!"," (missing formula parameters)");
	}

    return Compute(formula, params, removeDependencies);
}

std::vector<std::string> Formula::SplitParameters(const std::string &term)
{
    std::vector<std::string> result;
    std::string input = term;

    while (input != "")
    {
        auto arg = ConsumeFirstParameter(input);
        result.push_back(arg);
    }

    return result;
}

std::string Formula::ConsumeFirstParameter(std::string &term)
{
    std::string result;

    if (term[0] == '\"')
    {
        int stringEnd = term.find_first_of("\"");
        result = term.substr(0, stringEnd + 1);
        term = term.substr(stringEnd + 1, term.size());
    }

    else if (std::isalpha(term[0]) && term.find_first_of('(') < term.find_first_of(';'))
    {
        int doubleQuotes = 0;
        int openParenthesis = 0;
        int closedParenthesis = 0;

        int formulaEnd = 0;

        for (int i = 0; i < term.size(); i++)
        {
            if (doubleQuotes % 2 != 0)
            {
                continue;
            }

            if (openParenthesis && openParenthesis == closedParenthesis)
            {
                break;
            }

            if (term[i] == '(')
            {
                openParenthesis += 1;
            }

            if (term[i] == ')')
            {
                closedParenthesis += 1;
            }

            formulaEnd = i;
        }

        result = term.substr(0, formulaEnd + 1);
        term = term.substr(formulaEnd + 1, term.size());
    }

    else
    {
        int argumentEnd = term.find_first_of(';');
        result = argumentEnd == -1 ? term : term.substr(0, argumentEnd);
        result = Misc::Trim(result);
    }


    if (term == "")
    {
        return result;
    }

    int paramEnd = term.find_first_of(';');

    if (paramEnd == -1)
    {
        term = "";
        return result;
    }

    term = term.substr(paramEnd + 1, term.size());
    term = Misc::Trim(term);

    return result;
}

std::variant<std::monostate, std::string, double> Formula::Compute(const std::string& formula, std::vector<std::string>& params, bool removeDependencies)
{
	for (auto it = params.begin(); it < params.end(); it++)
	{
		std::vector<std::string> refs;
		if (!IsRefRange(*it, refs)) { continue; }
		it = params.erase(it);
		it = params.insert(it, refs.begin(), refs.end());
		it += refs.size() - 1;
	}

	if (std::regex_match(formula, std::regex("SUM", std::regex_constants::icase))) { return ComputeSum(params, removeDependencies); }
	if (std::regex_match(formula, std::regex("COUNT", std::regex_constants::icase))) { return ComputeCount(params, removeDependencies); }
	if (std::regex_match(formula, std::regex("AVG", std::regex_constants::icase))) { return ComputeAverage(params, removeDependencies); }
	if (std::regex_match(formula, std::regex("MIN", std::regex_constants::icase))) { return ComputeMinMax(params, true, removeDependencies); }
	if (std::regex_match(formula, std::regex("MAX", std::regex_constants::icase))) { return ComputeMinMax(params, false, removeDependencies); }
	if (std::regex_match(formula, std::regex("MOD", std::regex_constants::icase))) { return ComputeModulusOrPower(params, true, removeDependencies); }
	if (std::regex_match(formula, std::regex("POW", std::regex_constants::icase))) { return ComputeModulusOrPower(params, false, removeDependencies); }
	if (std::regex_match(formula, std::regex("LEN", std::regex_constants::icase))) { return ComputeLength(params, removeDependencies); }
	if (std::regex_match(formula, std::regex("TRIM", std::regex_constants::icase))) { return ComputeTrim(params, removeDependencies); }
	if (std::regex_match(formula, std::regex("CONCAT", std::regex_constants::icase))) { return ComputeConcat(params, removeDependencies); }

	return Invalid("Invalid syntax!");
}

std::variant<std::monostate, std::string, double> Formula::ComputeReference(const std::string& reference, bool removeDependencies)
{
	auto dependencyAddress = sheet->CellTitleToAddress(reference);
	if (!sheet->Values().contains(dependencyAddress))
	{
		sheet->AddCell(dependencyAddress, "");
	}

	auto& cellPtr = sheet->Values().at(dependencyAddress);

	auto formCellPtr = dynamic_pointer_cast<FormulaCell>(cellPtr);

	if (formCellPtr)
	{
		formCellPtr->Update();
	}

	if (removeDependencies)
	{
		cellPtr->RemoveReferencingCell(this->address);
	}
	else
	{
		cellPtr->AddReferencingCell(this->address);
	}

	if (!formCellPtr)
	{
		return cellPtr->Value();
	}

	if (!formCellPtr->Valid())
	{
		return Invalid(std::format("{}{}{}", "Invalid argument! (", reference, ")"));
	}

	if (CircularDependency(this->address, dependencyAddress))
	{
		return Invalid(std::format("{}{}{}", "Circular dependency! (", reference, ")"));
	}

	return formCellPtr->Value();
}

std::variant<std::monostate, std::string, double> Formula::ComputeSum(const std::vector<std::string>& params, bool removeDependencies)
{
	double result = 0;
	auto values = ComputeParamValues(params, removeDependencies);
	for (const auto& value : values)
	{
		if (std::holds_alternative<std::monostate>(value))
		{
			return Invalid("Invalid parameters!");
		}

		if (std::holds_alternative<std::string>(value))
		{
			continue;
		}

		result += std::get<double>(value);
	}

	return result;
}

std::variant<std::monostate, std::string, double> Formula::ComputeCount(const std::vector<std::string>& params, bool removeDependencies)
{
	double result = 0;
	auto values = ComputeParamValues(params, removeDependencies);
	for (const auto& value : values)
	{
		if (std::holds_alternative<std::monostate>(value))
		{
			return Invalid("Invalid parameters!");
		}

		if (std::holds_alternative<std::string>(value))
		{
			continue;
		}

		result++;
	}

	return result;
}

std::variant<std::monostate, std::string, double> Formula::ComputeAverage(const std::vector<std::string>& params, bool removeDependencies)
{
	auto sum = ComputeSum(params);
	if (std::holds_alternative<std::monostate>(sum))
	{
		return Invalid("Invalid syntax!");
	}

    auto size = std::get<double>(ComputeCount(params));

    if (size == 0)
    {
        return Invalid("AVG: Can't divide by 0!");
    }

    return std::get<double>(sum) / size;
}

std::variant<std::monostate, std::string, double> Formula::ComputeMinMax(const std::vector<std::string>& params, bool min, bool removeDependencies)
{
	std::vector<double> result;
	auto values = ComputeParamValues(params, removeDependencies);
	for (const auto& value : values)
	{
		if (std::holds_alternative<std::monostate>(value))
		{
			return Invalid("Invalid parameters!");
		}

		if (std::holds_alternative<std::string>(value))
		{
			continue;
		}

		result.push_back(std::get<double>(value));
	}

	if (result.empty()) { return (double)0; }
	return min ? *std::ranges::min_element(result) : *std::ranges::max_element(result);
}

std::variant<std::monostate, std::string, double> Formula::ComputeModulusOrPower(const std::vector<std::string>& params, bool mod, bool removeDependencies)
{
	if (params.size() != 2)
	{
		return Invalid("Invalid parameters! (expected 2 arguments)");
	}

	auto values = ComputeParamValues(params, removeDependencies);
	for (const auto& value : values)
	{
		if (std::holds_alternative<std::monostate>(value) || std::holds_alternative<std::string>(value)) 
		{ 
			return Invalid("Invalid parameters!"); 
		}
	}

	double v1 = std::get<double>(values[0]);
	double v2 = std::get<double>(values[1]);

	return mod ? (v1 - (std::floor(v1 / v2) * v2)) : std::pow(v1, v2);
}

std::variant<std::monostate, std::string, double> Formula::ComputeLength(const std::vector<std::string>& params, bool removeDependencies)
{
	if (params.size() != 1)
	{
		return Invalid("Invalid parameters! (expected 1 argument)");
	}

	auto value = Compute(params[0], removeDependencies);
	if (std::holds_alternative<std::monostate>(value))
	{
		return Invalid(std::format("{}{}{}", "Invalid parameters! (", params[0], ")"));
	}
	
	auto result = std::holds_alternative<std::string>(value) ? std::get<std::string>(value).size() :
		std::to_string(std::get<double>(value)).size();

	return static_cast<double>(result);
}

std::variant<std::monostate, std::string, double> Formula::ComputeTrim(const std::vector<std::string>& params, bool removeDependencies)
{
	if (params.size() != 1)
	{
		return Invalid("Invalid parameters! (expected 1 argument)");
	}

	auto value = Compute(params[0], removeDependencies);

	if (std::holds_alternative<double>(value))
	{
		return std::to_string(std::get<double>(value));
	}

	auto text = std::get<std::string>(value);
	auto substrings = Misc::Split(text, ' ');
	std::string result = "";
	for (int i = 0; i < substrings.size() - 1; i++)
	{
		result.append(substrings[i]);
		result.push_back(' ');
	}
	result.append(substrings.back());

	return result;
}

std::variant<std::monostate, std::string, double> Formula::ComputeConcat(const std::vector<std::string>& params, bool removeDependencies)
{
	if (params.size() != 2)
	{
		return Invalid("Invalid parameters! (expected 2 arguments)");
	}

	auto values = ComputeParamValues(params, removeDependencies);
	std::string result;
	for (const auto& value : values)
	{
		if (std::holds_alternative<std::monostate>(value))
		{
			return Invalid("Invalid parameters!");
		}

		auto substr = std::holds_alternative<std::string>(value) ? std::get<std::string>(value) : std::to_string(std::get<double>(value));
		result.append(substr);
	}

	return result;
}

std::vector<std::variant<std::monostate, std::string, double>> Formula::ComputeParamValues(const std::vector<std::string>& params, bool removeDependencies)
{
	std::vector<std::variant<std::monostate, std::string, double>> result;
	for (const auto& param : params)
	{
		auto paramValue = Compute(param, removeDependencies);
		result.push_back(paramValue);
	}

	return result;
}

std::variant<std::monostate, std::string, double> Formula::Invalid(const std::string& message)
{
	valid = false;
	errorMessage = message;
	return std::monostate{};
}

std::variant<std::monostate, std::string, double> Formula::Invalid(const std::string& message, const std::string& element)
{
	valid = false;
	errorMessage = std::format("{}{}", message, element);
	return std::monostate{};
}

bool Formula::IsString(const std::string& input)
{
    int quotesCount = std::ranges::count(input, '\"');
    return quotesCount == 2 && input.front() == '\"' && input.back() == '\"';
}

bool Formula::IsNumber(const std::string& input, double& output)
{
	return Misc::IsNumber(input, output);
}

bool Formula::IsReference(const std::string& input)
{
	auto refSyntax = std::regex("^[a-z]+[1-9][0-9]*$", std::regex_constants::icase);
	return std::regex_match(input, refSyntax);
}

bool Formula::IsRefRange(const std::string& input, std::vector<std::string>& output)
{
	int separatorIndex = static_cast<int>(input.find_first_of(':'));

	if (separatorIndex <= 0)
	{
		return false;
	}

	std::vector<std::string> refs = Misc::Split(input, ':');
	std::for_each(refs.begin(), refs.end(), [](std::string& ref) { ref = Misc::Trim(ref); });
	for (const std::string& ref : refs)
	{
		if (!IsReference(ref)) { return false; }
	}

	Address address1 = sheet->CellTitleToAddress(refs[0]);
	Address address2 = sheet->CellTitleToAddress(refs[1]);
	int startCol = address1.Col() < address2.Col() ? address1.Col() : address2.Col();
	int endCol = address1.Col() > address2.Col() ? address1.Col() : address2.Col();
	int startRow = address1.Row() < address2.Row() ? address1.Row() : address2.Row();
	int endRow = address1.Row() > address2.Row() ? address1.Row() : address2.Row();

	refs.clear();
	for (int col = startCol; col <= endCol; col++)
	{
		auto colTitle = Misc::GenerateColTitle(col);
		for (int row = startRow; row <= endRow; row++)
		{
			auto rowTitle = Misc::GenerateRowTitle(row);

			std::string cellTitle = std::format("{}{}", colTitle, rowTitle);
			refs.push_back(cellTitle);
		}
	}

    output = refs;
    return true;
}

bool Formula::IsRefRange(const std::string &input)
{
    int separatorIndex = static_cast<int>(input.find_first_of(':'));

    if (separatorIndex <= 0)
    {
        return false;
    }

    std::vector<std::string> refs = Misc::Split(input, ':');
    std::for_each(refs.begin(), refs.end(), [](std::string& ref) { ref = Misc::Trim(ref); });
    for (const std::string& ref : refs)
    {
        if (!IsReference(ref)) { return false; }
    }

    return true;
}

bool Formula::CircularDependency(const Address& currentAddress, const Address& referencedAddress)
{
	if (currentAddress == referencedAddress)
	{
		return true;
	}

	if (!sheet->Values().contains(currentAddress))
	{
		return false;
	}

	auto& referencingThis = sheet->Values().at(currentAddress)->Referencing();
	if (referencingThis.empty())
	{
		return false;
	}

	auto circular = std::ranges::find(referencingThis, referencedAddress);
	if (circular != referencingThis.end())
	{
		return true;
	}

	for (const auto& referencingAddress : referencingThis)
	{
		if (CircularDependency(referencingAddress, referencedAddress))
		{
			return true;
		}
	}

	return false;
}
