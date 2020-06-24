#include "label.h"
#include <GL/glut.h>

#define FONT_SIZE 18.0
#define FONT GLUT_BITMAP_HELVETICA_18

void Label::render()
{
	constexpr number FONT_HEIGHT{ FONT_SIZE };
	const Dimension &pad = padding(); // aliasing

	// Calculate minimal size of label
	Dimension minimal_caption_size(pad.width * 2.0, FONT_HEIGHT + (pad.height * 2.0), SCREEN);
	for (const str::value_type c : caption)
	{
		minimal_caption_size.width = minimal_caption_size.width + glutBitmapWidth(FONT, c);
	}

	minimal_caption_size = minimal_caption_size.to_cartesian();
	actual_padding = padding().to_cartesian();

	// Adjust width
	if (minimal_caption_size.width >= orginal_dimension.width)
		dimensions.width = minimal_caption_size.width;
	else
		actual_padding.width = actual_padding.width + ((orginal_dimension.width - minimal_caption_size.width) / 2.0);

	// Adjust height
	if (minimal_caption_size.height >= orginal_dimension.height)
		dimensions.height = minimal_caption_size.height;
	else
		actual_padding.height = actual_padding.height + ((orginal_dimension.height - minimal_caption_size.height) / 2.0);

	RectangleComponent::render();
}

void Label::additional_render_instruction() const
{
	const Dimension &pad = actual_padding; // aliasing
	glColor4d(text_color().r, text_color().g, text_color().b, text_color().a);
	glRasterPos2d(point.x + pad.width, point.y - dimensions.height + (pad.height) + Dimension(0.0, FONT_SIZE / 4.0, SCREEN).to_cartesian().height);
	for (const str::value_type c : caption)
		glutBitmapCharacter(FONT, c);
}