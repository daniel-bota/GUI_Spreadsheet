#pragma once
#include "Cell.h"

class TextCell : public Cell
{
public:
    TextCell(const Address& address, Sheet* sheet);
    TextCell(const Address& address, Sheet* sheet, const std::string& newValue);
	std::string ValueString() const override;
};

