#include <algorithm>

#include "libraries/engine/SwitcherEngine.hpp"

#include "libraries/graphic/components/frame/frame.h"
#include "libraries/graphic/components/button/button.h"
#include "libraries/graphic/components/window/window.h"
#include "libraries/graphic/components/label/label.h"
#include "libraries/graphic/components/lbutton/lbutton.h"
#include "libraries/graphic/components/drag_n_drop/drag_n_drop.h"

WINDOW_STARTUP()

struct Proxy : public SwitcherEngineInterface<DragAndDrop>, public DragAndDrop
{
	Proxy(
		RectangleComponent *comp, 
		ModifyMeAndExternal _on_drop = [](arg_type me, arg_type not_me){ std::cout << "drop" << std::endl; },
		ModifyMe _swap_visual_effect = [](arg_type) { return; },  
		ModifyMe _on_drag = [](arg_type) { std::cout << "drag" << std::endl; }
	)
		:DragAndDrop(comp, _on_drop, _swap_visual_effect, _on_drag) {}

	virtual uint64_t get_id() const override
	{
		return id;
	}

	virtual void swap(SwitcherEngineInterface<DragAndDrop>* out) override
	{
		// swap pointer owners
		RectangleComponent* tmp{ internal_component.get() };
		internal_component = out->get()->internal_component;
		out->get()->internal_component = tmp;

		// swap positions
		const Point p = internal_component()->point;
		internal_component()->change_position( out->get()->internal_component()->point );
		out->get()->internal_component()->change_position( p );

		// request for sync
		out->get()->set_require_sync(true);
		get()->set_require_sync(true);
	}

	virtual DragAndDrop* get() { return this; }

	inline friend bool operator<(const Proxy& p1, const Proxy p2) { return p1.get_id() < p2.get_id(); }
	inline friend bool operator==(const Proxy& p1, const Proxy p2) { return p1.get_id() == p2.get_id(); }
	inline friend bool operator!=(const Proxy& p1, const Proxy p2) { return p1.get_id() != p2.get_id(); }
};


int main(int argc, char **argv)
{
	MAIN_INIT("APP", argc, argv);

	SwitcherEngine<NUMBER_OF_FIELDS, DragAndDrop> engine;

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

	auto get_coord = [&](RectangleComponent* p) -> coord
	{
		for(int i = 0; i < NUMBER_OF_FIELDS; i++)
			for(int j = 0; j < NUMBER_OF_FIELDS; j++)
				if(engine[i][j]->get()->get_base_component(engine[i][j]->get(), true) == p ) return coord{ i, j };
		assert(false);
	};

	// Drawing
	for (int i = 0; i < NUMBER_OF_FIELDS; i++)
		for (int j = 0; j < NUMBER_OF_FIELDS; j++)
		{
			engine[i][j] = new Proxy{
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

						// new Label{
						// 	first_tile + Dimension{move.width * i, move.height * (-j), CARTESIAN},	   /* position of tile (operator+ is moving point by vector) */
						// 	tile_size,																   /* dimension of single tile */
						// 	std::to_string(i) + " ; " + std::to_string(j),
						// 	Colors::black,
						// 	next_color()
						// },

						//Example 3:

						new RectangleComponent{
							first_tile + Dimension{move.width * i, move.height * (-j), CARTESIAN}, /* position of tile (operator+ is moving point by vector) */
							tile_size,															   /* dimension of single tile */
							next_color()
						},


						{2.5, 2.5, SCREEN},
						next_color()},
					[&](arg_type inter, arg_type exter)
					{
						const coord c1 = get_coord( inter );
						const coord c2 = get_coord( exter );

						std::cout << "drop: " << c1 << " on: "<< c2<<  std::endl;
						if(engine.swap(c1, c2)) std::cout << "Swapped!" << std::endl;
						inter->require_sync = true;
						exter->require_sync = true;
					}
					// ,[](arg_type val) { if(val->color.r > 1.0) val->color = val->color - 1.0; else val->color = val->color + 1.0; }
					};
			window.add_component( engine[i][j]->get(), true );
		}

	engine.empty = { NUMBER_OF_FIELDS-1, NUMBER_OF_FIELDS-1 };

	window.start();

	return 0;
}