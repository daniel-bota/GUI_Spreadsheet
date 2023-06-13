#pragma once
#include "../Coordinates/Address.h"
#include <string>
#include <variant>
#include <memory>
#include <format>
#include <regex>
#include <algorithm>

class FormulaCell;
class Sheet;

class Formula
{
public:
	Formula() = default;
	Formula(Sheet* sheet, Address address, std::string expression);
	void Parse(bool removeDependencies = false);
	bool Valid() const { return valid; }
	std::variant<std::monostate, std::string, double> Value() const;
	const std::string& Expression() const { return expression; }
	const std::string& ErrorMessage() const { return errorMessage; }
private:
	std::string expression;
	std::variant<std::monostate, std::string, double> value;
	Sheet* sheet = nullptr;
	Address address{ -1, -1 };
	bool valid = true;
	std::string errorMessage{ "" };

	std::variant<std::monostate, std::string, double> Compute(std::string input, bool removeDependencies = false);
	std::variant<std::monostate, std::string, double> Compute(std::string formula, std::vector<std::string>& params, bool removeDependencies = false);
	std::variant<std::monostate, std::string, double> ComputeReference(std::string reference, bool removeDependencies);
	std::variant<std::monostate, std::string, double> ComputeSum(const std::vector<std::string>& params, bool removeDependencies = false);
	std::variant<std::monostate, std::string, double> ComputeCount(const std::vector<std::string>& params, bool removeDependencies = false);
	std::variant<std::monostate, std::string, double> ComputeAverage(const std::vector<std::string>& params, bool removeDependencies = false);
	std::variant<std::monostate, std::string, double> ComputeMinMax(const std::vector<std::string>& params, bool min, bool removeDependencies = false);
	std::variant<std::monostate, std::string, double> ComputeModulusOrPower(const std::vector<std::string>& params, bool mod, bool removeDependencies = false);
	std::variant<std::monostate, std::string, double> ComputeLength(const std::vector<std::string>& params, bool removeDependencies);
	std::variant<std::monostate, std::string, double> ComputeTrim(const std::vector<std::string>& params, bool removeDependencies);
	std::variant<std::monostate, std::string, double> ComputeConcat(const std::vector<std::string>& params, bool removeDependencies);
	std::vector<std::variant<std::monostate, std::string, double>> ComputeParamValues(const std::vector<std::string>& params, bool removeDependencies = false);
	std::variant<std::monostate, std::string, double> Invalid(std::string message);
	std::variant<std::monostate, std::string, double> Invalid(std::string message, std::string element);

	bool IsString(std::string input);
	bool IsNumber(std::string input, double& output);
	bool IsReference(std::string input);
	bool IsRefRange(std::string input, std::vector<std::string>& output);
	bool CircularDependency(const Address& currentAddress, const Address& referencedAddress);
};

