#pragma once
#include "Coordinates.h"
class Position : public Coordinates
{
public:
	Position() : Coordinates() {};
	Position(int screenXAxisIndex, int screenYAxisIndex) : Coordinates(screenXAxisIndex, screenYAxisIndex) {};
};

