#pragma once

#include "../component/component.h"

class Clickable : virtual public Component
{
public:
  virtual bool click(const Point&) = 0;
};
