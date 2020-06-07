#pragma once

#include <iostream>
#include "Point.h"


struct AllowPositive
{
	AllowPositive(const number val) { if(val < 0.0) THROW_MSG( std::invalid_argument, "value have to be positive" ); }
};

using unum_prop = _Property< number, AllowPositive >;

struct Dimension
{
	unum_prop width{ 0.0 };
	unum_prop height{ 0.0 };

	coord_system_prop system;

	Dimension() = default;
	Dimension(const number _width, const number _height, const coord_system_prop _system ) : width{ _width }, height{ _height  } { system = _system; }

	Dimension to_pixel() const noexcept;
	Dimension to_cartesian() const noexcept;
};

inline std::ostream& operator<<(std::ostream& os, const Dimension& d)
{
    return os << "[ " << d.width << " x " << d.height <<" ]";
}

Point operator+(const Point pnt, const Dimension &dim);
Dimension operator*(const Dimension &dim, const number num);