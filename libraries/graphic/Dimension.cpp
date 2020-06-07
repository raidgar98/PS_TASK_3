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

Point operator+(const Point pnt, const Dimension &dim)
{
	const Point p{pnt.system == CARTESIAN ? pnt : pnt.to_cartesian()};
	const Dimension d{dim.system == CARTESIAN ? dim : dim.to_cartesian()};

	const Point ret(p.x + d.width, p.y + d.height, CARTESIAN);
	return (pnt.system == CARTESIAN ? ret : ret.to_pixel() );
}

Dimension operator*(const Dimension &dim, const number num)
{
	const Dimension d{dim.system == CARTESIAN ? dim : dim.to_cartesian()};
	const Dimension ret( d.width * num, d.height * num, CARTESIAN );
	return (ret.system == CARTESIAN ? ret : ret.to_pixel() );
}