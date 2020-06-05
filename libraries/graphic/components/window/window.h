#pragma once

#include "../component/component.h"


#include <set>
#include <map>
#include <list>

#define WINDOW_STARTUP()                               \
	std::unique_ptr<Window> __window_ptr;                \
	void _____display____() { __window_ptr->display(); } \
	void _____on_click______(int button, int state, int x, int y) { __window_ptr->on_click(button, state, x, y); }
#define MAIN_INIT(title, argc, argv)                           \
	__window_ptr = std::make_unique<Window>(title, &argc, argv); \
	Window &window = *__window_ptr;                              \
	glutDisplayFunc(_____display____);                           \
	glutMouseFunc(_____on_click______);

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

	mutable points_collection points;
	property_type property;
	uint64_t help_id = 0;
	uint64_t get_id() const noexcept { return ptr_to_int(property.get_pointer()); }

	static uint64_t next() { return __items++; }
	inline static uint64_t __items = 1;
};


inline bool operator<(const shape &sh1, const shape &sh2) 
{
	/* Data will be sorted like:
	[ is_dynamic, get_id(), help_id ]

		[0, 0, 0]
		[0, 1, 1]
		[0, 1, 2]
		[0, 1, 4]
		[0, 2, 0]
		[0, 3, 0]
		[1, 0, 0]
		[1, 0, 1]
		[1, 0, 2]
		[1, 0, 6]
		[1, 1, 0]
		[1, 2, 2]
		[1, 3, 9]
	*/
	//sort priority: is_dynamic > get_id() > help_id
	if(sh1.property.get_flag(shape::IS_DYNAMIC) == sh2.property.get_flag(shape::IS_DYNAMIC))
	{
		if( sh1.get_id() == sh2.get_id() )
			return sh1.help_id < sh2.help_id;
		else return sh1.get_id() < sh2.get_id();

	}else return sh1.property.get_flag(shape::IS_DYNAMIC) < sh2.property.get_flag(shape::IS_DYNAMIC);
}
inline bool operator==(const shape &sh1, const shape &sh2) { return sh1.get_id() == sh2.get_id(); }
inline bool operator!=(const shape &sh1, const shape &sh2) { return !(sh1 == sh2); }

class Window
{
	// using shape = std::pair< color, points_collection >;
	using list_of_components = std::list<component_type>;
	using list_of_shapes = std::set<shape>;
	using prepared_objects = std::map<int32_t, list_of_shapes>;

	list_of_components components;
	prepared_objects objects;

	void prepare_drawing(const property_type &component);
	void prepare_static();

public:

	explicit Window(const std::string &str, int *argc, char **argv);
	~Window()
	{
		objects.clear();
		for(component_type& cmp : components )
		{
			component* tmp = cmp.get_pointer();
			if( tmp != nullptr)
			{
				delete tmp;
				tmp = nullptr;
			}
		}
		components.clear();
	}

	void start();
	void add_component(component *cmp, const bool is_dynamic = false);
	void display();
	void on_click(int button, int state, int x, int y);

	friend std::function<bool(Window &)> get_async_lambda();
};

std::function<bool(Window &)> get_async_lambda();
