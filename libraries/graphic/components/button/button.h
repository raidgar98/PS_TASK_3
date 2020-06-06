#pragma once

#include <functional>

#include "../clickable/clickable.h"
#include "../rectangle_component/rectangle_component.h"

using ClickCallback = std::function<void()>;

class Button : public rectangle_component, public Clickable
{
public:
  ClickCallback onClick;

  Button(const Point _point, const Dimension _dim, const ClickCallback &_onClick, const Color& c = Colors::RGB( 0.4, 0.4, 0.4 ))
      : rectangle_component{_point, _dim, c}, onClick{_onClick} {}

  ~Button() {}

  virtual bool click(const Point& p) override;
};
