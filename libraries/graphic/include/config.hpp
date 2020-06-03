#pragma once

#include <GL/glut.h>
#include <GL/glu.h>

#include <cassert>
#include <cmath>
#include <functional>
#include <vector>
#include <memory>

#include "../../utility/Property.hpp"

enum COORDINATE_SYSTEM
{
	CARTESIAN,
	SCREEN
};

using number = double;
using num_prop = Property<number>;
using coord_system_prop = Property<COORDINATE_SYSTEM>;

template<typename T>
constexpr number to_number(const T val) { return static_cast<number>(val); }

constexpr size_t NUMBER_OF_FIELDS{ 4ul };

inline number get_window_width()
{
	const number ret = to_number(glutGet( GLUT_WINDOW_WIDTH ));
	return ( ret ? ret : 300ul );
}

inline number get_window_height()
{
	const number ret = to_number(glutGet( GLUT_WINDOW_HEIGHT ));
	return ( ret ? ret : 500ul );
}
