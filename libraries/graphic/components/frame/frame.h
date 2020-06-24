#pragma once

#include "../rectangle_component/rectangle_component.h"
#include "../wrapper/wrapper.h"

struct Frame : public RectangleComponent, public Wrapper<RectangleComponent>
{
	Dimension thickness;

	Frame() = delete;
	Frame(RectangleComponent *comp, const Dimension& thick, const Color &frame_color = Colors::black)
		: Wrapper{comp}, RectangleComponent{{0.0, 0.0, CARTESIAN}, {0.0, 0.0, CARTESIAN}, frame_color}
	{
		if (thick.system != COORDINATE_SYSTEM::CARTESIAN)
			thickness = thick.to_cartesian();
		else
			thickness = thick;

		update_position();
	}

	~Frame() {}
	virtual str name() const override { return std::string{ std::string{ "Frame<" } + internal_component.get()->name() + ">"}.c_str(); }
	virtual void render() override;
	virtual void change_position(const Point& p) override
	{
		Wrapper::change_position(p);
		// update_position();
		render();
	}

protected:

	void update_position();
};
