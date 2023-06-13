#pragma once
#include "Cell.h"
#include <variant>
#include "Formula.h"

enum Status
{
	UpToDate,
	OutOfDate
};

class FormulaCell : public Cell
{
public:
	FormulaCell(Address address, Sheet* sheet) : Cell(address, sheet) {};
	FormulaCell(Address address, Sheet* sheet, Formula formula) : Cell(address, sheet), formula(formula) {};

	std::variant<std::monostate, std::string, double> GetUpdated();
	std::variant<std::monostate, std::string, double> Value() const override;
	std::string ValueString() const override;

	const std::string& Expression() const;
	const std::string& ErrorMessage() const;
	bool Valid() const;
	void SetFormula(Formula newForm);
	Status Status() const { return status; }
	void NotifyOutOfDate(Address notificationSource);
	void Update(bool removeDependencies = false);
private:
	Formula formula;
	enum Status status = UpToDate;
};

