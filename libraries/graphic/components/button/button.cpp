#include "button.h"

bool Button::click(const Point &p) const
{
  if (rectangle_component::is_in_my_area(p))
  {
    onClick();
    return true;
  }
  else
    return false;
}