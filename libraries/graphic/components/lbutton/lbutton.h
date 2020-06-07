#pragma once

#include "../button/button.h"
#include "../label/label.h"

class LButton : public Button, public Label
{

//Label(const Point &pnt, const Dimension &dmn, const str &caption, const Color &text_color = Colors::black, const Color &background_color = Colors::invisible, const Dimension &_padding = Dimension{5.0, 5.0, SCREEN}.to_cartesian())
// Button(const Point _point, const Dimension _dim, const ClickCallback &_onClick, const Color& c = Colors::RGB( 0.4, 0.4, 0.4 ))
public:
  LButton(const Point _point, const Dimension _dim, const str& caption, const ClickCallback &_onClick, const Dimension&_padd, const Color& _background_color = Colors::RGB(0.4, 0.4, 0.4), const Color& _text_color = Colors::black)
    :Button{_point, _dim, _onClick, _background_color}, Label{_point, _dim, caption, _text_color, _background_color, _padd}, RectangleComponent{_point, _dim, _background_color}
    {}

  virtual str name() const override { return "LButton"; }
};
