#include "Sheet.h"
#include "Cell/Formula.h"
#include "Cell/FormulaCell.h"
#include "Cell/TextCell.h"
#include "Cell/NumericCell.h"
#include "Misc/Misc.h"

void Sheet::AddCell(const Address& address, const std::string& input)
{
	std::shared_ptr<Cell> cellPtr = nullptr;
	if (values.contains(address))
	{
		cellPtr = values.at(address);

		auto formCellPtr = std::dynamic_pointer_cast<FormulaCell>(cellPtr);
		if (formCellPtr)
		{
			formCellPtr->Update(true);
		}

		if (input == "" && cellPtr->Referencing().empty())
		{
            values.erase(address);
            return;
		}
	}
	
	double number;
	if (input[0] == '=')
	{
		Formula formula(this, address, input);
        AddCell(std::make_shared<FormulaCell>(address, this, formula));
	}
    else if (Misc::IsNumber(input, number))
	{
        AddCell(std::make_shared<NumericCell>(address, this, number));
	}
	else
	{
        AddCell(std::make_shared<TextCell>(address, this, input));
	}

    if (cellPtr == nullptr)
    {
        return;
	}

    cellPtr->NotifyReferencingCells(address);
}

void Sheet::Initialize(const std::map<Address, std::shared_ptr<Cell>>& importedValues)
{
	values.clear();

	for (const auto& pair : importedValues)
	{
		auto formCell = std::dynamic_pointer_cast<FormulaCell>(pair.second);
		if (formCell)
		{
			AddCell(pair.first, formCell->Expression());
			continue;
		}
		AddCell(pair.first, pair.second->ValueString());
	}
}

void Sheet::AddCell(std::shared_ptr<Cell> cell)
{
	values[cell->GetAddress()] = cell;
}

Address Sheet::CellTitleToAddress(const std::string& title)
{
	auto firstDigitIndex = std::ranges::find_if(title, [](const char& c) { return std::isdigit(c); }) - title.begin();
	std::string colTitle = title.substr(0, firstDigitIndex);
	for (char& c : colTitle)
	{
		c = toupper(c);
	}
	std::string rowTitle = title.substr(firstDigitIndex, title.size());

	int colIndex = ColTitleToIndex(colTitle);
	int rowIndex = std::stoi(rowTitle) - 1;

	return Address{ colIndex, rowIndex };
}

int Sheet::ColTitleToIndex(const std::string& colTitle)
{
    auto input = colTitle;
	const int base = 26;
	int result = 0;
    for (char c : input)
	{
        input.erase(input.begin());
        result += (c - 'A' + 1) * static_cast<int>(pow(base, input.size()));
	}

	return result - 1;
}

nlohmann::json Sheet::Serialize()
{
	nlohmann::json output;

	for (auto it = values.begin(); it != values.end(); it++)
	{
		const std::pair<Address, std::shared_ptr<Cell>>& value = *it;

		auto cellTitle = std::get<1>(value)->Title();

		int column = std::get<0>(value).Col();
		int row = std::get<0>(value).Row();

		auto& cellPtr = std::get<1>(value);
		auto formCellPtr = std::dynamic_pointer_cast<FormulaCell>(cellPtr);
		auto cellValue = formCellPtr ?
			formCellPtr->Expression() : cellPtr->ValueString();

		
		output[cellTitle]["column"] = column;
		output[cellTitle]["row"] = row;
		output[cellTitle]["value"] = cellValue;
	}

	return output;
}

bool Sheet::Deserialize(const nlohmann::json& source)
{
	std::map<Address, std::string> initializerList{};

	for (const auto& element : source.items())
	{
		try
		{
			int col = source.at(element.key()).at("column");
			int row = source.at(element.key()).at("row");
			auto newAddress = Address(col, row);
			std::string value = source.at(element.key()).at("value");

			initializerList[newAddress] = value;
		}
		catch (const nlohmann::json::out_of_range& ex)
		{
			return false;
		}	
	}

	Initialize();

	for (const auto& pair : initializerList)
	{
        auto address = std::get<0>(pair);
        auto value = std::get<1>(pair);
        AddCell(address, value);
	}

	return true;
}
