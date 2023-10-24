#include "NumericCell.h"

NumericCell::NumericCell(const Address& address, Sheet* sheet) : Cell(address, sheet)
{
    value = static_cast<double>(0);
}

NumericCell::NumericCell(const Address& address, Sheet* sheet, double newValue) : Cell(address, sheet)
{
    value = newValue;
}

std::string NumericCell::ValueString() const
{
    return std::to_string(std::get<double>(value));
}
