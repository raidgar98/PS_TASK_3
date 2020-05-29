#pragma once

#include <cmath>
#include "../utility/Property.hpp"

using number = double;

struct Point
{
	const Property<number> x;
	const Property<number> y;

	Point(const number _x, const number _y) : x{_x}, y{_y} {}
};