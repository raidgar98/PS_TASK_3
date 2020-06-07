#pragma once

#include "../../include/Dimension.h"
#include "../../include/Point.h"
#include "../../include/config.hpp"

#include "../../../submodules/sneaky_pointer/sneaky_pointer.hpp"

using Color = ::color;
using point = Point;
using point_ptr = std::shared_ptr<point>;

struct drawing_instruction{ ReadOnyProperty<uint64_t> id; std::vector<point> points; Color color; std::function<void()> additional_instructions = [](){ return; }; };
using drawing_instruction_collection = std::vector<drawing_instruction>;

struct Component
{
	ReadOnyProperty<uint64_t> id;

	Component() : id{ ++__id }{}
	virtual void render(drawing_instruction_collection&) = 0;
	virtual void additional_render_instruction() const { return; }
	virtual void resize() { return; }
	virtual bool move() { return false; };
	virtual ~Component() {}

private:

	inline static uint64_t __id{ 0ul };

};

using property_type = sneaky_pointer<Component, 1>;
using component_type = sneaky_pointer<Component, 1>;
