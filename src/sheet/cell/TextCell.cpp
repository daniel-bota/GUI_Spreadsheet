#include "TextCell.h"

TextCell::TextCell(const Address& address, Sheet* sheet) : Cell(address, sheet)
{
	value = std::string{ "" };
}

TextCell::TextCell(const Address& address, Sheet* sheet, const std::string& newValue) : Cell(address, sheet)
{
	value = newValue;
}

std::string TextCell::ValueString() const
{
	return std::get<std::string>(value);
}
