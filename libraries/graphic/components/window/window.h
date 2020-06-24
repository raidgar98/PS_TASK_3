#pragma once

#include "../component/component.h"

#include <set>
#include <map>
#include <list>

#define WINDOW_STARTUP()                                                                                           \
	std::unique_ptr<Window> __window_ptr;                                                                          \
	void _____display____() { __window_ptr->display(); }                                                           \
	void _____on_click______(int button, int state, int x, int y) { __window_ptr->on_click(button, state, x, y); } \
	void _____window_size_changed______(int, int) { __window_ptr->window_size_changed(); }
#define MAIN_INIT(title, argc, argv)                             \
	__window_ptr = std::make_unique<Window>(title, &argc, argv); \
	Window &window = *__window_ptr;                              \
	glutDisplayFunc(_____display____);                           \
	glutMouseFunc(_____on_click______);                          \
	glutReshapeFunc(_____window_size_changed______);

template <typename T>
constexpr uint64_t ptr_to_int(const T *ptr) { return reinterpret_cast<uint64_t>(ptr); }

template <typename T>
constexpr uint64_t ptr_to_int(T *ptr) { return reinterpret_cast<uint64_t>(ptr); }
constexpr int IS_DYNAMIC = 1;

class Window
{
	// using shape = std::pair< color, drawing_instruction >;
	using list_of_components = std::list<component_type>;
	
	list_of_components components;

	component_type drag{ nullptr };

	void prepare_drawing(const property_type &component);
	void preprocess_components();

public:
	explicit Window(const std::string &str, int *argc, char **argv);
	~Window();

	void start();
	Component* add_component(Component *cmp, const bool is_dynamic = false);
	void display();
	void on_click(int button, int state, int x, int y);
	void window_size_changed();

	friend std::function<bool(Window &)> get_async_lambda();
};

std::function<bool(Window &)> get_async_lambda();
