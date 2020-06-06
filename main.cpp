#include "libraries/graphic/components/frame/frame.h"
#include "libraries/graphic/components/button/button.h"
#include "libraries/graphic/components/window/window.h"

WINDOW_STARTUP()

int main(int argc, char **argv)
{
	MAIN_INIT( "APP", argc, argv );

	window.add_component( new frame{ new Button({-0.9, -0.65, CARTESIAN}, {50.0, 50.0, SCREEN}, []() { std::cout << "Button1 Click" << std::endl; }), Dimension{10.0, 10.0, SCREEN}, Colors::blue } );
	// window.add_component( new frame{ new Button({-0.9, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, []() { std::cout << "Button1 Click" << std::endl; }), Dimension{10.0, SCREEN}, Colors::blue } );
	window.add_component( new Button({-0.3, -0.65, CARTESIAN}, {50.0, 50.0, SCREEN}, []() { std::cout << "Button2 Click" << std::endl; }) );
	// window.add_component( new Button({-0.3, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, []() { std::cout << "Button2 Click" << std::endl; }) );
	window.add_component( new Button({0.3, -0.65, CARTESIAN}, {50.0, 50.0, SCREEN}, []() { std::cout << "Button3 Click" << std::endl; }) );
	// window.add_component( new Button({0.3, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, []() { std::cout << "Button3 Click" << std::endl; }) );

	window.start();

	return 0;
}