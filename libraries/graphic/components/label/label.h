#pragma once

#include <functional>

#include "../frame/frame.h"
#include "../rectangle_component/rectangle_component.h"

struct Label : public virtual RectangleComponent
{
  Property<Color> text_color;
  Property<Dimension> padding;

  Label(const Point &pnt, const Dimension &dmn, const str &caption, const Color &text_color = Colors::black, const Color &background_color = Colors::invisible, const Dimension &_padding = Dimension{5.0, 5.0, SCREEN}.to_cartesian())
      : RectangleComponent{pnt, dmn, background_color}, caption{caption}, text_color{text_color}
  {
    if (_padding.system != SCREEN) padding = _padding.to_pixel();
    else padding = _padding;

    if(dmn.system != CARTESIAN) orginal_dimension = dmn.to_cartesian();
    else orginal_dimension = dmn;
  }

  virtual void render(drawing_instruction_collection &) override;
  virtual bool move() override { return update_required; };
  void Caption(const str &text)
  {
    caption = text;
    update_required = true;
  }
  virtual void additional_render_instruction() const override;
  const str &Caption() const { return caption; }
  virtual void resize() override { update_required = true; }

protected:
  std::string caption;
  bool update_required = false;
  Dimension actual_padding;
  Dimension orginal_dimension;
};
