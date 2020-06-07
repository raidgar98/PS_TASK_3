#pragma once

#include "../rectangle_component/rectangle_component.h"
#include "../wrapper/wrapper.h"

// Have to 
struct DragAndDrop : public Wrapper<RectangleComponent>
{
	Property<Point> previous_position;
	Property<Point> offset;

	DragAndDrop(RectangleComponent *comp)
		:Wrapper{ comp } {}


	void drag(const Point&);
	void drop(const Point&);
	virtual bool move() override;

};
