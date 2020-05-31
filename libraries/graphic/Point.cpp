#include "include/Point.h"

#include <iostream>

number Point::get_distance(const Point &p) const noexcept
{
    return sqrt(std::pow(x - p.x, 2) + std::pow(y - p.y, 2));
}

Point Point::to_pixel() const noexcept
{
    assert( system == COORDINATE_SYSTEM::CARTESIAN );

    const number screenX = (( x + 1.0 ) * ( get_window_width() / 2.0 )) - 0.5;
    const number screenY = ( 1.0 - y ) *  ( get_window_height() / 2.0 ) - 0.5;
    // const number screenX = ( x / get_window_width() ) - 0.5;
    // const number screenY = ( y / get_window_height() ) - 0.5;

    return Point( screenX, screenY, COORDINATE_SYSTEM::SCREEN );
}

Point Point::to_cartesian() const noexcept
{
    assert( system == COORDINATE_SYSTEM::SCREEN );

    const number cartesianX = (( x + 0.5 ) / get_window_width()) * 2.0 - 1.0;
    const number cartesianY = 1.0 - (( y + 0.5) / get_window_height() ) * 2.0;
    // const number cartesianX = ( x + 0.5 ) * get_window_width();
    // const number cartesianY = ( y + 0.5 ) * get_window_height();

    return Point( cartesianX, cartesianY, COORDINATE_SYSTEM::CARTESIAN );
}

