#include "frame.h"

void frame::render(drawing_instruction_collection &ret) const
{
	internal_component->render(ret);
	rectangle_component::render(ret);
}

bool frame::move()
{
	if (this->internal_component->move())
	{
		update_position();
		return true;
	}
	else
		return false;
}

void frame::update_position()
{
	this->point = Point{
		internal_component->point.x - thickness.width,
		internal_component->point.y + ((internal_component->point.y >= 0.0 ? -1.0 : 1.0) * (thickness.height ) ),
		CARTESIAN
	};
	this->dimensions = Dimension{
		internal_component->dimensions.width + ( thickness.width * 2.0 ), 
		internal_component->dimensions.height + ( thickness.height * 2.0 ),
		CARTESIAN
	};
}

bool frame::click(const Point &p)
{
	if (Clickable *obj = dynamic_cast<Clickable *>(internal_component.operator rectangle_component *const &()))
		return obj->click(p);
	else
		return false;
}