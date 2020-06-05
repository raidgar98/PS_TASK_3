#pragma once

#include "../rectangle_component/rectangle_component.h"

struct frame : virtual public rectangle_component
{
    ReadOnyProperty<property_type> internal_component;
    
};
