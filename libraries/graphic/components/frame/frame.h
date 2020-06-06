#pragma once

#include "../rectangle_component/rectangle_component.h"
#include "../clickable/clickable.h"

struct frame : public rectangle_component, public Clickable
{
	ReadOnyProperty<rectangle_component *> internal_component;
	Dimension thickness;

	frame() = delete;

	frame(rectangle_component *comp, const Dimension& thick, const Color &frame_color = Colors::black)
		: internal_component{comp}, rectangle_component{{0.0, 0.0, CARTESIAN}, {0.0, 0.0, CARTESIAN}, frame_color}
	{
		assert(comp);

		if (thick.system != COORDINATE_SYSTEM::CARTESIAN)
			thickness = thick.to_cartesian();
		else
			thickness = thick;

		update_position();
	}

	~frame() {}

	virtual void render(drawing_instruction_collection &) const override;
	virtual bool move() override;
	virtual bool click(const Point &p) override;

protected:
	void update_position();
};
