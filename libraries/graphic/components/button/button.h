#pragma once

#include <functional>

#include "../clickable/clickable.h"
#include "../rectangle_component/rectangle_component.h"

using ClickCallback = std::function<void()>;

class Button : public rectangle_component, public Clickable
{
public:
  ClickCallback onClick;

  Button(const Point _point, const Dimension _dim, const ClickCallback &_onClick)
      : rectangle_component{_point, _dim}, onClick{_onClick} {}

  ~Button() {}

  virtual bool click(const Point& p) const override;
};
