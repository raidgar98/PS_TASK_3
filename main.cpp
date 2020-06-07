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
	window.add_component(new Frame{new Button({-0.9, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, []() { std::cout << "Button1 Click" << std::endl; }), Dimension{2.0, 2.0, SCREEN}, Colors::blue});
	window.add_component(new LButton({-0.3, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, "knefel", []() { std::cout << "Button2 Click" << std::endl; }, {2.0, 2.0, SCREEN}), true);
	window.add_component(new Frame{new LButton{{0.3, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, "kuba guzik", []() { std::cout << "Button3 Click" << std::endl; }, {2.0, 2.0, SCREEN}}, {2.0, 2.0, SCREEN}}, true);
	window.add_component(new Frame(new Label({-0.9, 0.1, CARTESIAN}, {0.001, 0.001, CARTESIAN}, "Whoa dziala, nie wiem czy powinno!", Colors::black, Colors::white), {2.0, 2.0, SCREEN}), true);
*/


	window.start();

	return 0;
}