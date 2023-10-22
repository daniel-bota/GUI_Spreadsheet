#pragma once
#include "Coordinates.h"

class Area : public Coordinates
{
public:
	Area(int width, int height) : Coordinates(width, height) {};

	int Width() const { return X(); };
	int Height() const { return Y(); };
};

