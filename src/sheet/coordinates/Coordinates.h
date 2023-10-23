#pragma once

class Coordinates
{
public:
	virtual ~Coordinates() {};

	Coordinates() = default;
	Coordinates(int x, int y) : x(x), y(y) {};

	bool operator==(const Coordinates& other) const;
	bool operator!=(const Coordinates& other) const;
	bool operator<(const Coordinates& other) const;

	int X() const { return x; }
	int Y() const { return y; }

private:
	int x{ -1 };
	int y{ -1 };
};

