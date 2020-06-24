#include "frame.h"

void Frame::render()
{
	Wrapper::render();
	update_position();
	RectangleComponent::render();
}

void Frame::update_position()
{
	this->point = Point(
		internal_component()->point.x - thickness.width,
		internal_component()->point.y + thickness.height,
		CARTESIAN
	);
	this->dimensions = Dimension(
		internal_component()->dimensions.width + ( thickness.width * 2.0 ), 
		internal_component()->dimensions.height + ( thickness.height * 2.0 ),
		CARTESIAN
	);
}
