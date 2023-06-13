#pragma once
#include "Cell.h"

class NumericCell : public Cell
{
public:
	NumericCell(Address address, Sheet* sheet);
	NumericCell(Address address, Sheet* sheet, double newValue);
	std::string ValueString() const override;
};

