#pragma once

#include <functional>
#include "../../include/Dimension.h"
#include "../../include/Point.h"

using ClickCallback = std::function<void()>;

class Button
{
public:

  Point point;
  Dimension dimensions;
  ClickCallback onClick;

  Button(const Point _point, const Dimension _dim, const ClickCallback& _onClick)
      : point{_point}, dimensions{ _dim }, onClick{ _onClick } {}

  ~Button() {}

  void CheckClick(const number x, const number y)
  {
    if (x >= point.x && x < point.x + dimensions.width && // x
        y <= point.y && y > point.y - dimensions.height) // y
    { 
      onClick();
    }
  }
};
