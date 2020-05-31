#include "include/Dimension.h"

Dimension Dimension::to_pixel() const noexcept
{
    assert( system == COORDINATE_SYSTEM::CARTESIAN );
    return Dimension{ width * get_window_width(), height * get_window_height() , SCREEN };
}

Dimension Dimension::to_cartesian() const noexcept
{
    assert( system == COORDINATE_SYSTEM::SCREEN );
    return Dimension{ width / get_window_width(), height / get_window_height() , CARTESIAN };
}
