#pragma once

#include "../../include/Dimension.h"
#include "../../include/Point.h"
#include "../../include/config.hpp"

#include "../../../submodules/sneaky_pointer/sneaky_pointer.hpp"

using Color = ::color;
using point = Point;
using point_ptr = std::shared_ptr<point>;

struct Component;

struct drawing_instruction{ Component* author; ReadOnyProperty<uint64_t> id; std::vector<point> points; Color color; std::function<void()> additional_instructions = [](){ return; }; };
using drawing_instruction_collection = std::vector<drawing_instruction>;

struct Component
{
	ReadOnyProperty<uint64_t> id;
	Property<bool> require_sync;

	Component() : id{ ++__id }{}
	virtual ~Component() {}

	// overload as much as you want
	virtual void additional_render_instruction() const { return; }
	virtual void resize() { return; }
	virtual void render(drawing_instruction_collection&) = 0;

	// think twice before overload
	virtual Component * get_child() { return this; }
	virtual void set_require_sync(const bool val) { require_sync = val; }

	// try not to overload
	virtual bool move() { if(require_sync){ require_sync = false; return true; } else return false; };

	// DEBUG:
	str my_name() const { return std::to_string( id.get() ) + name(); }
	virtual str name() const { return "Component"; }

private:

	inline static uint64_t __id{ 0ul };

};

using property_type = sneaky_pointer<Component, 1>;
using component_type = sneaky_pointer<Component, 1>;
