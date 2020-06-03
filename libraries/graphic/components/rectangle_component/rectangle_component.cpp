#include "rectangle_component.h"
#include <iostream>

bool rectangle_component::is_in_my_area(const Point &_p) const
{
    Point p = _p;
    if (p.system != SCREEN)
        p = p.to_pixel();

    const Point tmp_p = point.to_pixel();
    const Dimension tmp_d = dimensions.to_pixel();

    bool ret = true;

    ret &= p.x >= tmp_p.x;
    ret &= p.x < tmp_p.x + tmp_d.width;
    ret &= p.y >= tmp_p.y;
    ret &= p.y < tmp_p.y + tmp_d.height;

    return ret;
}

drawing_instruction_collection rectangle_component::render() const
{
    points_collection ret;
    ret.reserve(4);

    const Point &_p = point;          //.to_cartesian();
    const Dimension &_d = dimensions; //.to_cartesian();

    ret.emplace_back(_p);
    ret.emplace_back(_p.x + _d.width, _p.y);
    ret.emplace_back(_p.x + _d.width, _p.y - _d.height);
    ret.emplace_back(_p.x, _p.y - _d.height);

    return {ret};
}

bool operator<(const rectangle_component &r1, const rectangle_component &r2) { return r1.point < r2.point; }
bool operator==(const rectangle_component &r1, const rectangle_component &r2) { return r1.point == r2.point; }
bool operator!=(const rectangle_component &r1, const rectangle_component &r2) { return !(r1 == r2); }