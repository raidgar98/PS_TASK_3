#pragma once

#include <cassert>
#include <cmath>
#include "../../utility/Property.hpp"

enum COORDINATE_SYSTEM
{
	CARTESIAN,
	SCREEN
};

using number = double;
using num_prop = Property<number>;
using coord_system_prop = Property<COORDINATE_SYSTEM>;

constexpr number WINDOW_WIDTH = 300u;
constexpr number WINDOW_HEIGHT = 500u;

template<typename T>
constexpr number to_number(const T val) { return static_cast<number>(val); }