#pragma once

#include "../../include/Dimension.h"
#include "../../include/Point.h"
#include "../../include/config.hpp"

using point = Point;
using point_ptr = std::shared_ptr<point>;
using points_collection = std::vector<point>;
using drawing_instruction_collection = std::vector<points_collection>;

class component
{
public:
    virtual drawing_instruction_collection render() const = 0;
};