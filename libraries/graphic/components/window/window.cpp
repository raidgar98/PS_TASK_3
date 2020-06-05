#include "window.h"
#include <thread>
#include <future>
#include "../button/button.h"

void Window::prepare_drawing(const property_type &component)
{
	assert(component.get_pointer());
	const uint64_t id = ptr_to_int(component.get_pointer());
	const auto &instructions = component->render();
	for (const auto &points : instructions)
	{
		assert(points.size() > 0);
		int32_t draw_type;

		switch (points.size())
		{
		case 1:
			draw_type = GL_POINT;
			break;
		case 2:
			draw_type = GL_LINE;
			break;
		case 3:
			draw_type = GL_TRIANGLES;
			break;
		case 4:
			draw_type = GL_QUADS;
			break;
		default:
			draw_type = GL_POLYGON;
			break;
		}

		auto found = objects.find(draw_type);
		if (found != objects.end()) // if found
		{
			auto it = found->second.lower_bound(shape{points, component}); // get range of theese which points to currently processed component

			if (it->get_id() != id) // add fresh points
			{
				objects[draw_type].emplace( shape{ points, component, shape::next() } );
			}
			else // update existing ones
			{
				while (it != found->second.end() && it->get_id() == id)
				{
					it->points = points;
					it++;
				}
			}
		}
		else
			objects[draw_type] = list_of_shapes{{points, component, shape::next()}};
	}
}

void Window::display()
{
	auto lamda = get_async_lambda();

	// update dynamic components while static ones will be processed
	std::future<bool> ready = std::async(std::launch::async, [&]() { return lamda(*this); });

	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, get_window_width(), get_window_height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-1,1,-1,1, -1,1);

	auto render_objects = [&](const bool dynamic) {
		// filter
		property_type prop{components.begin()->get_pointer()};
		prop.set_flag(shape::IS_DYNAMIC, dynamic);
		shape filter{{}, prop};

		//iterate over categories of primitives
		for (const auto &var : objects)
		{
			// get range of processed ones (static - false, dynamic - true)
			auto it = var.second.lower_bound(filter);

			// start rendering this category
			glBegin(var.first);

			// iterate as long as range and filter is kept
			while (it != var.second.end() && it->property.get_flag(shape::IS_DYNAMIC) == dynamic)
			{
				// get color once instead of four
				const color tmp_color = it->property->color;

				// paint
				glColor4d(tmp_color.r, tmp_color.g, tmp_color.b, tmp_color.a);

				// clue - render shape
				for (const point &pnt : it->points)
					glVertex2d(pnt.x, pnt.y);

				it++;
			}

			// stop rendering
			glEnd();
		}
	};

	// render static objects
	render_objects(false);

	// wait for end of processing
	ready.wait();

	// render dynamic objects
	render_objects(true);

	// additional render instructions
	for (component_type &prop : components)
		prop->additional_render_instruction();

	// push to GPU
	glFlush();
}

Window::Window(const std::string &str, int *argc, char **argv)
{
	glutInit(argc, argv);
	glutInitWindowSize(get_window_width(), get_window_height());
	glutCreateWindow(str.c_str());
}

void Window::prepare_static()
{
	for (const component_type &comp : components)
		if (comp.get_flag(shape::IS_DYNAMIC) == false)
			prepare_drawing(comp);
}

void Window::on_click(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			// clicks
			const Point clip{to_number(x), to_number(y), SCREEN};
			for (component_type &ptr : components)
				if (Clickable *btn = dynamic_cast<Clickable *>(ptr.get_pointer()))
				{
					if (btn->click(clip))
						break;
				}

			// hold down (TODO)
		}
		else if (state == GLUT_UP)
		{
			// hold up` (TODO)
		}
	}
}

void Window::add_component(component *cmp, const bool is_dynamic)
{
	assert(cmp);
	component_type tmp{cmp};
	tmp.set_flag(shape::IS_DYNAMIC, is_dynamic);
	components.emplace_back(tmp);
}

void Window::start()
{
	prepare_static();
	glutMainLoop();
}

std::function<bool(Window &)> get_async_lambda()
{
	return [](Window &wnd) -> bool {
		for (const auto &comp : wnd.components)
			if (comp.get_flag(shape::IS_DYNAMIC) && comp->move())
				wnd.prepare_drawing(comp);
		return true;
	};
}