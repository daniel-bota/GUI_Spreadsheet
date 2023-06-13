#include "TextCell.h"
#include "../Misc/Misc.h"

TextCell::TextCell(Address address, Sheet* sheet) : Cell(address, sheet)
{
	value = std::string{ "" };
}

TextCell::TextCell(Address address, Sheet* sheet, std::string newValue) : Cell(address, sheet)
{
	value = newValue;
}

std::string TextCell::ValueString() const
{
	return std::get<std::string>(value);
}
