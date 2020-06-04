#include "include/Dimension.h"

Dimension Dimension::to_pixel() const noexcept
{
    assert( system == COORDINATE_SYSTEM::CARTESIAN );
    return Dimension{ width * ( get_window_width() / 2.0 ), height * (get_window_height() / 2.0) , SCREEN };
}

Dimension Dimension::to_cartesian() const noexcept
{
    assert( system == COORDINATE_SYSTEM::SCREEN );
    return Dimension{ width / ( get_window_width() / 2.0 ), height / ( get_window_height() / 2.0 ) , CARTESIAN };
}
