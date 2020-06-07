#include "button.h"

bool Button::click(const Point &p)
{
  if (RectangleComponent::is_in_my_area(p))
  {
    onClick();
    return true;
  }
  else
    return false;
}