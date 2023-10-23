#pragma once
#include <string>
#include <vector>
#include "../Coordinates/Address.h"
#include <memory>
#include <variant>

class Sheet;
class FormulaCell;

class Cell
{
public:
	virtual ~Cell() = default;
    explicit Cell(Address address, Sheet* sheet);

	//virtual ValueString
    virtual std::string ValueString() const = 0;
    virtual const std::variant<std::monostate, std::string, double>& Value() const { return value; }
    const std::string& Title() const { return title; }
    const Address& GetAddress() const { return address; }
	const std::vector<Address>& Referencing() const { return referencing; }
	void SetReferencingCells(const std::vector<Address>& newReferencing);
    void AddReferencingCell(const Address& address);
    void RemoveReferencingCell(const Address& address);
    void NotifyReferencingCells();
    void NotifyReferencingCells(const Address& notificationSource);

protected:
    void GenerateTitle(const std::string& colTitle, const std::string& rowTitle);
	std::string GenerateRowTitle(int index) const;
	std::string GenerateColTitle(int index) const;

	class Address address { -1, -1 };
	std::string title{ "" };
	std::variant<std::monostate, std::string, double> value;
    Sheet* sheet;
	std::vector<Address> referencing{};
};

