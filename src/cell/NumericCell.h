#pragma once
#include "Cell.h"

class NumericCell : public Cell
{
public:
    NumericCell(const Address& address, Sheet* sheet);
    NumericCell(const Address& address, Sheet* sheet, double newValue);
	std::string ValueString() const override;
};

