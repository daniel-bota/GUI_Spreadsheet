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
    FormulaCell(const Address& address, Sheet* sheet) : Cell(address, sheet) {};
    FormulaCell(const Address& address, Sheet* sheet, const Formula& formula) : Cell(address, sheet), formula(formula) {};

    const std::variant<std::monostate, std::string, double>& GetUpdated();
    const std::variant<std::monostate, std::string, double>& Value() const override;
    std::string ValueString() const override;

	const std::string& Expression() const;
	const std::string& ErrorMessage() const;
	bool Valid() const;
    void SetFormula(const Formula& newForm);
    const Status& Status() const { return status; }
    void NotifyOutOfDate(const Address& notificationSource);
	void Update(bool removeDependencies = false);
private:
	Formula formula;
	enum Status status = UpToDate;
};

