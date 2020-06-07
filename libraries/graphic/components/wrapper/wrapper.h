#pragma once

#include "../clickable/clickable.h"

template <typename T>
struct Wrapper : public Clickable
{
	Property<T *> internal_component;
	Dimension thickness;

	Wrapper() = delete;
	Wrapper(T *comp) : internal_component{comp}
	{
		// static_assert(dynamic_cast<Component *>(comp));
		assert(comp);
	}

	~Wrapper()
	{
		T *ptr = internal_component();
		std::memset(&internal_component, 0, sizeof(ReadOnyProperty<T *>)); // brutal but works :)
		delete ptr;
		ptr = nullptr;
	}

	virtual void render(drawing_instruction_collection &src) override { internal_component()->render(src); }
	virtual bool move() override { return internal_component()->move(); }
	virtual void click(const Point &p) override
	{
		if (Clickable *obj = dynamic_cast<Clickable *>(internal_component()))
			obj->click(p);
	}

	virtual bool hit(const Point &p) override
	{
		if (Clickable *obj = dynamic_cast<Clickable *>(internal_component()))
			return obj->hit(p);
		else
			return false;
	}

	virtual Component * get_child() override { return internal_component(); }

	virtual void additional_render_instruction() const override { internal_component()->additional_render_instruction(); };
	virtual void resize() { internal_component()->resize(); }
	virtual str name() const override { return std::string{std::string{"Wrapper<"} + internal_component.get()->name() + ">"}.c_str(); }
};
