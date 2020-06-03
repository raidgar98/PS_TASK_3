#pragma once

#include "../component/component.h"

#include <set>
#include <map>
#include <list>
#include <cstring>

#define WINDOW_STARTUP() std::unique_ptr<Window> __window_ptr; void _____display____() { __window_ptr->display(); } void _____on_click______(int button, int state, int x, int y) { __window_ptr->on_click(button, state, x, y); } 

#define MAIN_INIT( title, argc, argv ) __window_ptr = std::make_unique<Window>( title, &argc, argv ); Window& window = *__window_ptr; glutDisplayFunc( _____display____ ); glutMouseFunc( _____on_click______ );

template<typename T>
constexpr uint64_t ptr_to_int( const T* ptr ) { return reinterpret_cast< uint64_t >( ptr ); }

template<typename T>
constexpr uint64_t ptr_to_int( T* ptr ) { return reinterpret_cast< uint64_t >( ptr ); }

struct color
{
	double r, g, b, a;
};
inline bool operator==(const color& c1, const color& c2) { return std::memcmp( &c1, &c2, sizeof(color) ) == 0; }
inline bool operator!=(const color& c1, const color& c2) { return !(c1 == c2); }

struct shape
{
  mutable color colour;
  mutable points_collection points;
  const uint64_t id = 0;
};

inline bool operator<(const shape& sh1, const shape& sh2) { return sh1.id < sh2.id; }
inline bool operator==(const shape& sh1, const shape& sh2) { return sh1.id == sh2.id; }
inline bool operator!=(const shape& sh1, const shape& sh2) { return !(sh1 == sh2); }

class Window
{
  // using shape = std::pair< color, points_collection >;
  using list_of_shapes = std::set< shape >;
  using prepared_objects = std::map<int32_t, list_of_shapes >;

  std::set<component*> objects;
  prepared_objects prepared_static_objects;
  prepared_objects prepared_dynamic_objects;
  number last_height;
  number last_width;

  void prepare_drawing(const color &, const component *, prepared_objects&);
  void prepare_static();

public:

  explicit Window(const std::string& str, int* argc, char **argv);
  ~Window();

  void start() { prepare_static(); glutMainLoop(); }
  void add_component( component * cmp ) { objects.insert( cmp ); }
  void display();
  void on_click(int button, int state, int x, int y);
};
