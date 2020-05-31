#pragma once

#include "../../utility/Property.hpp"
#include "config.hpp"

struct Dimension
{
	const num_prop width;
	const num_prop height;

	Dimension(const number _width, const number _height) : width{ std::abs( _width ) }, height{  std::abs(_height)  } {}
	Dimension(const Dimension&) = default;
	Dimension(Dimension&&) = default;
};