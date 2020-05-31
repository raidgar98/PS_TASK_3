#pragma once

#include <iostream>

#include "../../utility/Property.hpp"
#include "config.hpp"

struct Dimension
{
	num_prop width{ 0.0 };
	num_prop height{ 0.0 };

	coord_system_prop system = COORDINATE_SYSTEM::SCREEN;

	Dimension() = default;
	Dimension(const number _width, const number _height, const coord_system_prop _system = COORDINATE_SYSTEM::SCREEN) : width{ std::abs( _width ) }, height{  std::abs(_height)  }, system{ _system } {}
	// Dimension(const Dimension&) = default;
	// Dimension(Dimension&&) = default;

	Dimension to_pixel() const noexcept;
	Dimension to_cartesian() const noexcept;
};

inline std::ostream& operator<<(std::ostream& os, const Dimension& d)
{
    return os << "[ " << d.width << " x " << d.height <<" ]";
}
