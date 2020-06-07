#pragma once

#include <GL/glut.h>
#include <GL/glu.h>

#include <cassert>
#include <cmath>
#include <functional>
#include <vector>
#include <memory>
#include <cstring>
#include <iostream>

#include "../../utility/Property.hpp"

enum COORDINATE_SYSTEM
{
	CARTESIAN = 1,
	SCREEN = 2
};

struct ValidateEnum
{
	ValidateEnum( const COORDINATE_SYSTEM& val ) { assert( val == CARTESIAN || val ==SCREEN ); }
};

using number = double;
using str = std::string;
using num_prop = Property<number>;
using coord_system_prop = _Property<COORDINATE_SYSTEM, ValidateEnum>;

template<typename T>
constexpr number to_number(const T val) { return static_cast<number>(val); }

constexpr size_t NUMBER_OF_FIELDS{ 4ul };

inline number get_window_width()
{
	const number ret = to_number(glutGet( GLUT_WINDOW_WIDTH ));
	return ( ret ? ret : 500ul );
}

inline number get_window_height()
{
	const number ret = to_number(glutGet( GLUT_WINDOW_HEIGHT ));
	return ( ret ? ret : 500ul );
}

struct color
{
	number r, g, b, a = 1.0;
};

inline bool operator==(const color& c1, const color& c2) { return std::memcmp( &c1, &c2, sizeof(color) ) == 0; }
inline bool operator!=(const color& c1, const color& c2) { return !(c1 == c2); }

inline std::ostream& operator<<(std::ostream& ost, const ::color& c)
{
	ost << "RGBA( " << c.r << ", " << c.g << ", " << c.b << ", " << c.a << " )";
	return ost;
}

namespace Colors
{
	constexpr color invisible{ 0.0, 0.0, 0.0, 0.0 };
	constexpr color black{ 0.0, 0.0, 0.0 };
	constexpr color white{ 1.0, 1.0, 1.0 };
	constexpr color red{ 1.0, 0.0, 0.0 };
	constexpr color green{ 0.0, 1.0, 0.0 };
	constexpr color blue{ 0.0, 0.0, 1.0 };
	constexpr color RGBA(const number R, const number G, const number B, const number A) { return { R, G, B, A }; };
	constexpr color RGB(const number R, const number G, const number B) { return RGBA( R, G, B, 1.0 ); };
};