#pragma once

#include "../component/component.h"

struct rectangle_component : public component
{
    Point point;
    Dimension dimensions;

    rectangle_component(const Point _point, const Dimension _dim)
    {
        if (_point.system != COORDINATE_SYSTEM::CARTESIAN)
            point = _point.to_cartesian();
        else
            point = _point;

        if(_dim.system != COORDINATE_SYSTEM::CARTESIAN)
            dimensions = _dim.to_cartesian();
        else
            dimensions = _dim;
    }

    bool is_in_my_area(const Point &p) const;

    virtual drawing_instruction_collection render() const override;
};

inline std::ostream& operator<<(std::ostream& os, const rectangle_component& rec)
{
    return os << "rectangle_component: " << rec.point << rec.dimensions << std::endl;
}