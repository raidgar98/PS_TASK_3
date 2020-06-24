#pragma once

#include "../../include/Dimension.h"
#include "../../include/Point.h"
#include "../../include/config.hpp"

#include <list>

#include "../../../submodules/sneaky_pointer/sneaky_pointer.hpp"

using Color = ::color;
using point = Point;
using point_ptr = std::shared_ptr<point>;

struct Component;

struct drawing_instruction{ std::vector<point> points; Color color; std::function<void()> additional_instructions = [](){ return; }; };
using drawing_instruction_collection = std::list<drawing_instruction>;

struct Component
{
	using prepared_objects = std::map<int32_t, drawing_instruction_collection >;

	ReadOnyProperty<uint64_t> id;
	Property<bool> require_sync;
	Property<prepared_objects> shapes;

	Component() : id{ ++__id }{}
	virtual ~Component() {}

	// overload as much as you want
	virtual void additional_render_instruction() const { return; }
	virtual void resize() { return; }
	virtual void render() = 0;

	// think twice before overload
	virtual Component * get_child() { return this; }
	virtual void set_require_sync(const bool val) { require_sync = val; }

	// try not to overload
	virtual bool move() { if(require_sync){ require_sync = false; return true; } else return false; };

	virtual void change_position(const Point&) = 0;

	// DEBUG
	str my_name() const { return std::to_string( id.get() ) + name(); }
	virtual str name() const { return "Component"; }

protected:

	void add_shape(const drawing_instruction& i)
	{
		int32_t draw_type;

		switch (i.points.size())
		{
		case 1:
			draw_type = GL_POINT;
			break;
		case 2:
			draw_type = GL_LINE;
			break;
		case 3:
			draw_type = GL_TRIANGLES;
			break;
		case 4:
			draw_type = GL_QUADS;
			break;
		default:
			draw_type = GL_POLYGON;
			break;
		}

		auto found = shapes().find(draw_type);
		if (found != shapes().end()) found->second.push_back(i);
		else shapes()[draw_type] = { i };
	}

private:

	inline static uint64_t __id{ 0ul };

};

using property_type = sneaky_pointer<Component, 1>;
using component_type = sneaky_pointer<Component, 1>;
