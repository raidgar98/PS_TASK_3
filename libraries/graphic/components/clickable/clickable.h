#pragma once

#include "../component/component.h"

class Clickable : virtual public component
{
public:
  virtual bool click(const Point&) const = 0;
};
