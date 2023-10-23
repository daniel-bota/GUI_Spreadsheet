#pragma once
#include "Coordinates.h"

class Address : public Coordinates
{
public:
	Address() = default;
	Address(int columnIndex, int rowIndex) : Coordinates(columnIndex, rowIndex) {};

	int Col() const
	{
		return X();
	}

	int Row() const
	{
		return Y();
	}
};

