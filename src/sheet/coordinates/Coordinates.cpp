#include "Coordinates.h"

bool Coordinates::operator==(const Coordinates& other) const
{
	return x == other.x && y == other.y;
}

bool Coordinates::operator!=(const Coordinates& other) const
{
	return !(*this == other);
}

bool Coordinates::operator<(const Coordinates& other) const
{
	if (y == other.y)
	{
		return x < other.x;
	}

	return y < other.y;
}