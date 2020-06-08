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

struct shape
{
	enum FLAGS : uint8_t
	{
		IS_DYNAMIC = 1
	};

	mutable drawing_instruction instr;
	property_type property;
	uint64_t get_id() const noexcept { return instr.id; }
};

inline bool operator<(const shape &sh1, const shape &sh2)
{
	if (sh1.property.get_flag(shape::IS_DYNAMIC) == sh2.property.get_flag(shape::IS_DYNAMIC))
	{
		return sh1.get_id() > sh2.get_id();
	}
	else
		return sh1.property.get_flag(shape::IS_DYNAMIC) < sh2.property.get_flag(shape::IS_DYNAMIC);
}
inline bool operator==(const shape &sh1, const shape &sh2) { return sh1.get_id() == sh2.get_id(); }
inline bool operator!=(const shape &sh1, const shape &sh2) { return !(sh1 == sh2); }

class Window
{
	// using shape = std::pair< color, drawing_instruction >;
	using list_of_components = std::list<component_type>;
	using list_of_shapes = std::set<shape>;
	using prepared_objects = std::map<int32_t, list_of_shapes>;

	list_of_components components;
	prepared_objects objects;

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
