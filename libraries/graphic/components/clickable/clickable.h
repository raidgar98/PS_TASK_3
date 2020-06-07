#pragma once

#include "../component/component.h"

class Clickable : virtual public Component
{
public:
  virtual str name() const override { return "Clickable"; }
  virtual void click(const Point&) = 0;
  virtual bool hit(const Point&) = 0;
};
