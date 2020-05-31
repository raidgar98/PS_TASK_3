#pragma once

#include <functional>

#include "../rectangle_component/rectangle_component.h"

using ClickCallback = std::function<void()>;

class Button : public rectangle_component
{
public:
  ClickCallback onClick;

  Button(const Point _point, const Dimension _dim, const ClickCallback &_onClick)
      : rectangle_component{_point, _dim}, onClick{_onClick} {}

  ~Button() {}

  bool CheckClick(const Point& p) const
  {
    if (rectangle_component::is_in_my_area(p))
    {
      onClick();
      return true;
    } else return false;
  }
};
