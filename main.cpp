#include <algorithm>

#include "libraries/engine/SwitcherEngine.hpp"

#include "libraries/graphic/components/frame/frame.h"
#include "libraries/graphic/components/button/button.h"
#include "libraries/graphic/components/window/window.h"
#include "libraries/graphic/components/label/label.h"
#include "libraries/graphic/components/lbutton/lbutton.h"
#include "libraries/graphic/components/drag_n_drop/drag_n_drop.h"

WINDOW_STARTUP()

int main(int argc, char **argv)
{
	MAIN_INIT("APP", argc, argv);

	SwitcherEngine<NUMBER_OF_FIELDS, num, false> engine;
	num __icrementator = 10000;
	engine.reset([&](const bool){ return __icrementator++; });

	const number color_offset{0.1};
	const number color_limit{0.8};
	const number color_step{0.3};

	std::set<Color> colors;
	for (number r = color_offset; r < color_limit; r += color_step)
		for (number g = color_offset; g < color_limit; g += color_step)
			for (number b = color_offset; b < color_limit; b += color_step)
				colors.insert(Colors::RGB(r, g, b));

	auto color_iterator = colors.begin();
	auto next_color = [&]() {
		color_iterator++;
		if (color_iterator == colors.end())
			color_iterator = colors.begin();
		return *color_iterator;
	};
	/*
//	Examples:

	window.add_component(new Frame{new Button({-0.9, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, []() { std::cout << "Button1 Click" << std::endl; }), Dimension{2.0, 2.0, SCREEN}, Colors::blue});
	window.add_component(new LButton({-0.3, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, "knefel", []() { std::cout << "Button2 Click" << std::endl; }, {2.0, 2.0, SCREEN}), true);
	window.add_component(new Frame{new LButton{{0.3, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, "kuba guzik", []() { std::cout << "Button3 Click" << std::endl; }, {2.0, 2.0, SCREEN}}, {2.0, 2.0, SCREEN}}, true);
	window.add_component(new Frame(new Label({-0.9, 0.1, CARTESIAN}, {0.001, 0.001, CARTESIAN}, "Whoa dziala, nie wiem czy powinno!", Colors::black, Colors::white), {2.0, 2.0, SCREEN}), true);
*/

	// Setup
	// spacing between tiles
	const Dimension spacing = Dimension{3.0, 3.0, SCREEN}.to_cartesian();

	// position of first tile
	const Point first_tile{-0.9, 0.9, CARTESIAN};

	// vector to move next tile
	const Dimension move{
		((std::abs(first_tile.x) * 2.0) / D_NUMBER_OF_FIELDS) + spacing.width,
		((std::abs(first_tile.y) * 2.0) / D_NUMBER_OF_FIELDS) + spacing.height,
		CARTESIAN};

	// sizze of single tile ( without borders )
	const Dimension tile_size{
		((std::abs(first_tile.x) * 2.0) - ((NUMBER_OF_FIELDS - 1.0) * move.width)),
		((std::abs(first_tile.y) * 2.0) - ((NUMBER_OF_FIELDS - 1.0) * move.height)),
		CARTESIAN};

	// Drawing
	for (int i = 0; i < NUMBER_OF_FIELDS; i++)
		for (int j = 0; j < NUMBER_OF_FIELDS; j++)
		{
			window.add_component(
				new DragAndDrop{
					new Frame{
						//Example 1:

						// new LButton{
						// 	first_tile + Dimension{move.width * i, move.height * (-j), CARTESIAN},	   /* position of tile (operator+ is moving point by vector) */
						// 	tile_size,																   /* dimension of single tile */
						// 	std::to_string(i) + ";" + std::to_string(j),							   /* text on button */
						// 	[](Component *com) { std::cout << "click: ( " << com->id << " )" << std::endl; }, /* what to do on click */
						// 	{2.0, 2.0, SCREEN},
						// 	next_color() /* minimal padding */
						// },

						// Example 2:

						new Label{
							first_tile + Dimension{move.width * i, move.height * (-j), CARTESIAN},	   /* position of tile (operator+ is moving point by vector) */
							tile_size,																   /* dimension of single tile */
							std::to_string(i),
							Colors::black,
							next_color()
						},

						//Example 3:

						// new RectangleComponent{
						// 	first_tile + Dimension{move.width * i, move.height * (-j), CARTESIAN}, /* position of tile (operator+ is moving point by vector) */
						// 	tile_size,															   /* dimension of single tile */
						// 	next_color()
						// },


						{2.5, 2.5, SCREEN},
						next_color()},
					[&](arg_type inter, arg_type exter)
					{
						// Here some tile logic
						swap_drag_n_drop(inter, exter);
					},
					[](arg_type val) { if(val->color.r > 1.0) val->color = val->color - 1.0; else val->color = val->color + 1.0; }},
				true /* dynamic = true ( it will be asked is changed every time it is rendered, otherwise it will never be checked ) */
			);
		}

	window.start();

	return 0;
}