#pragma once

#include "../../include/Dimension.h"
#include "../../include/Point.h"
#include "../../include/config.hpp"

#include "../../../submodules/sneaky_pointer/sneaky_pointer.hpp"

using point = Point;
using point_ptr = std::shared_ptr<point>;
using points_collection = std::vector<point>;
using drawing_instruction_collection = std::vector<points_collection>;

struct component
{
    Property<typename ::color> color = Colors::invisible;

    virtual drawing_instruction_collection render() const = 0;
    virtual void additional_render_instruction() const { return; }
    virtual bool move() { return false; };
    virtual ~component() {}
};

using property_type = sneaky_pointer<component, 1, false>;
using component_type = sneaky_pointer<component, 1, true>;
