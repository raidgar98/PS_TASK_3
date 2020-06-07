#pragma once

#include "../clickable/clickable.h"

template <typename T>
struct Wrapper : public Clickable
{
	ReadOnyProperty<T *> internal_component;
	Dimension thickness;

	Wrapper() = delete;
	Wrapper(T *comp) : internal_component{comp}
	{
		// static_assert(dynamic_cast<Component *>(comp));
		assert(comp);
	}

	virtual void render(drawing_instruction_collection &src) override { internal_component()->render(src); }
	virtual bool move() override { return internal_component()->move(); }
	virtual bool click(const Point &p) override
	{
		if (Clickable *obj = dynamic_cast<Clickable *>(internal_component())) return obj->click(p);
		else return false;
	}
	virtual void additional_render_instruction() const override { internal_component()->additional_render_instruction(); };
	virtual void resize() { internal_component()->resize(); }
};
