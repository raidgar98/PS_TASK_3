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

void rectangle_component::render(drawing_instruction_collection &f_ret) const
{
	assert( this->point.system == CARTESIAN && this->dimensions.system == CARTESIAN );
	const Point &_p = point;          //.to_cartesian();
	const Dimension &_d = dimensions; //.to_cartesian();

	f_ret.emplace_back(drawing_instruction{ id, std::initializer_list<Point>{
		_p,
		{ _p.x + _d.width, _p.y, CARTESIAN },
		{ _p.x + _d.width, _p.y - _d.height, CARTESIAN },
		{ _p.x, _p.y - _d.height, CARTESIAN }
	}, color });

	if(true)
		std::cout << std::endl;
}

bool operator<(const rectangle_component &r1, const rectangle_component &r2) { return r1.point < r2.point; }
bool operator==(const rectangle_component &r1, const rectangle_component &r2) { return r1.point == r2.point; }
bool operator!=(const rectangle_component &r1, const rectangle_component &r2) { return !(r1 == r2); }