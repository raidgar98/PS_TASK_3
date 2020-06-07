#pragma once

#include "../rectangle_component/rectangle_component.h"
#include "../clickable/clickable.h"

struct Frame : public RectangleComponent, public Clickable
{
	ReadOnyProperty<RectangleComponent *> internal_component;
	Dimension thickness;

	Frame() = delete;

	Frame(RectangleComponent *comp, const Dimension& thick, const Color &frame_color = Colors::black)
		: internal_component{comp}, RectangleComponent{{0.0, 0.0, CARTESIAN}, {0.0, 0.0, CARTESIAN}, frame_color}
	{
		assert(comp);

		if (thick.system != COORDINATE_SYSTEM::CARTESIAN)
			thickness = thick.to_cartesian();
		else
			thickness = thick;

		update_position();
	}

	~Frame() {}

	virtual void render(drawing_instruction_collection &) override;
	virtual bool move() override;
	virtual bool click(const Point &p) override;
	virtual void additional_render_instruction() const override { internal_component()->additional_render_instruction(); };
	virtual void resize() { internal_component()->resize(); }

protected:
	void update_position();
};
