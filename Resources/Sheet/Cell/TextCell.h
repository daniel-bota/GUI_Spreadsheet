#pragma once
#include "Cell.h"

class TextCell : public Cell
{
public:
	TextCell(Address address, Sheet* sheet);
	TextCell(Address address, Sheet* sheet, std::string newValue);
	std::string ValueString() const override;
};

