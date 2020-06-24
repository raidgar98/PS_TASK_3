#pragma once

#include "../component/component.h"

struct RectangleComponent : virtual public Component
{
    Point point;
    Dimension dimensions;
    Color color;// = Colors::invisible;

    RectangleComponent(const Point& _point, const Dimension& _dim, const Color& c = Colors::black)
    {
        if (_point.system != COORDINATE_SYSTEM::CARTESIAN)
            point = _point.to_cartesian();
        else
            point = _point;

        if(_dim.system != COORDINATE_SYSTEM::CARTESIAN)
            dimensions = _dim.to_cartesian();
        else
            dimensions = _dim;

        color = c;
    }

    bool is_in_my_area(const Point &p) const;
    virtual str name() const override { return "RectangleComponent"; }
    virtual void render() override;
    virtual void change_position(const Point& p) { point = p; render(); set_require_sync(true); }
};

inline std::ostream& operator<<(std::ostream& os, const RectangleComponent& rec)
{
    return os << "rectangle_component: " << rec.point << rec.dimensions << std::endl;
}