#include "libraries/graphic/components/frame/frame.h"
#include "libraries/graphic/components/button/button.h"
#include "libraries/graphic/components/window/window.h"
#include "libraries/graphic/components/label/label.h"
#include "libraries/graphic/components/lbutton/lbutton.h"

WINDOW_STARTUP()

int main(int argc, char **argv)
{
	MAIN_INIT("APP", argc, argv);

/*
//	Examples:

	window.add_component(new Frame{new Button({-0.9, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, []() { std::cout << "Button1 Click" << std::endl; }), Dimension{2.0, 2.0, SCREEN}, Colors::blue});
	window.add_component(new LButton({-0.3, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, "knefel", []() { std::cout << "Button2 Click" << std::endl; }, {2.0, 2.0, SCREEN}), true);
	window.add_component(new Frame{new LButton{{0.3, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, "kuba guzik", []() { std::cout << "Button3 Click" << std::endl; }, {2.0, 2.0, SCREEN}}, {2.0, 2.0, SCREEN}}, true);
	window.add_component(new Frame(new Label({-0.9, 0.1, CARTESIAN}, {0.001, 0.001, CARTESIAN}, "Whoa dziala, nie wiem czy powinno!", Colors::black, Colors::white), {2.0, 2.0, SCREEN}), true);
*/

	// Setup
	// spacing between tiles
	const Dimension spacing = Dimension{ 3.0, 3.0, SCREEN }.to_cartesian();

	// position of first tile
	const Point first_tile{ -0.9, 0.9, CARTESIAN };

	// vector to move next tile
	const Dimension move{
		(( std::abs(first_tile.x) * 2.0 ) / D_NUMBER_OF_FIELDS) + spacing.width,
		(( std::abs(first_tile.y) * 2.0 ) / D_NUMBER_OF_FIELDS) + spacing.height,
		CARTESIAN
	};

	// sizze of single tile ( without borders )
	const Dimension tile_size{ 
		(( std::abs(first_tile.x) * 2.0 ) - (( NUMBER_OF_FIELDS - 1.0 ) * move.width )  ),
		(( std::abs(first_tile.y) * 2.0 ) - (( NUMBER_OF_FIELDS - 1.0 ) * move.height )  ),
		CARTESIAN
	};

	// Drawing 
	for(int i = 0; i < NUMBER_OF_FIELDS; i++)
		for(int j = 0; j < NUMBER_OF_FIELDS; j++)
			window.add_component( 
				new Frame{
					new LButton{
						first_tile + Dimension{ move.width * i , move.height * (-j) , CARTESIAN },		/* position of tile */
						tile_size,	/* dimension of single tile */
						std::to_string( i ) + ";" + std::to_string(j),	/* text on button */
						[=](){ std::cout << "( " << i << " ; " << j << " )" << std::endl; },	/* what to do on click */
						{ 2.0, 2.0, SCREEN }		/* minimal padding */
					}, { 1.0, 1.0, SCREEN }, Colors::red		/* thickness and color of frame */
				}, true		/* dynamic = true ( it will be asked is changed every time it is rendered, otherwise it will never be checked ) */
			);

	window.start();

	return 0;
}