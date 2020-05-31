#include "include/Point.h"

#include <iostream>

number Point::get_distance(const Point &p) const noexcept
{
    return sqrt(std::pow(x - p.x, 2) + std::pow(y - p.y, 2));
}

Point Point::to_pixel() const noexcept
{
    assert( system == COORDINATE_SYSTEM::CARTESIAN );

    const number screenX = (( x + 1.0 ) * ( WINDOW_WIDTH / 2.0 ));
    const number screenY = ( 0.0 - y ) +  ( WINDOW_HEIGHT / 2.0 );  // TODO: repair it

    return Point( screenX, screenY, COORDINATE_SYSTEM::SCREEN );
}

Point Point::to_cartesian() const noexcept
{
    assert( system == COORDINATE_SYSTEM::SCREEN );

    const number cartesianX = ( x - ( WINDOW_WIDTH / 2.0 ) ) / ( WINDOW_WIDTH / 2.0 );
    const number cartesianY = 0.0 - ( ( y - ( WINDOW_HEIGHT / 2.0 ) ) / ( WINDOW_HEIGHT / 2.0 ) );

    return Point( cartesianX, cartesianY, COORDINATE_SYSTEM::CARTESIAN );
}

