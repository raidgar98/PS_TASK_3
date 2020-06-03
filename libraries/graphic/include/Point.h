#pragma once

#include "config.hpp"
#include <iostream>

struct Point
{
	num_prop x{ 0.0 };
	num_prop y{ 0.0 };

	coord_system_prop system = COORDINATE_SYSTEM::SCREEN;

	Point() = default;
	Point(const number _x, const number _y, const COORDINATE_SYSTEM _system = COORDINATE_SYSTEM::SCREEN) 
		: x{_x}, y{_y}, system{ _system } {}

	number get_distance(const Point&) const noexcept;
	Point to_pixel() const noexcept;
	Point to_cartesian() const noexcept;

};

inline bool operator<(const Point& p1, const Point& p2) { return ( p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x ); }
inline bool operator==(const Point& p1, const Point& p2) { return (p1.x == p2.x) && (p1.y == p2.y); }
inline bool operator!=(const Point& p1, const Point& p2) { return !(p1 == p2); }


inline std::ostream& operator<<(std::ostream& os, const Point& p)
{
    return os << "( " << p.x << " ; " << p.y <<" )";
}