#include "Cell.h"
#include "../Sheet.h"
#include "../Misc/Misc.h"
#include "Resources/Sheet/Cell/FormulaCell.h"
#include <format>

Cell::Cell(Address address, Sheet* sheet) : address(address), sheet(sheet)
{
	GenerateTitle(GenerateColTitle(address.Col()), GenerateRowTitle(address.Row()));
}

void Cell::SetReferencingCells(const std::vector<Address>& newReferencing)
{
	referencing = newReferencing;
}

void Cell::AddReferencingCell(const Address& address)
{
	auto existing = std::ranges::find(referencing, address);
	if (existing != referencing.end())
	{
		return;
	}
	referencing.push_back(address);
}

void Cell::RemoveReferencingCell(const Address& address)
{
	auto existing = std::ranges::find(referencing, address);
	if (existing == referencing.end())
	{
		return;
    }
    referencing.erase(existing);
}

void Cell::NotifyReferencingCells()
{
    NotifyReferencingCells(this->GetAddress());
}

void Cell::NotifyReferencingCells(const Address& notificationSource)
{
	for (const auto& address : referencing)
	{
		auto cell = std::dynamic_pointer_cast<FormulaCell>(sheet->Values().at(address));
		cell->NotifyOutOfDate(notificationSource);
	}
}

void Cell::GenerateTitle(std::string colTitle, std::string rowTitle)
{
	title = std::format("{}{}", colTitle, rowTitle);
}

std::string Cell::GenerateRowTitle(int index) const
{
	return Misc::GenerateRowTitle(index);
}

std::string Cell::GenerateColTitle(int index) const
{
	return Misc::GenerateColTitle(index);
}
