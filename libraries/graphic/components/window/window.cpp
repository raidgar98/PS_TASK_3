#include "window.h"
#include <thread>
#include <future>
#include <iostream>
#include "../button/button.h"

void Window::prepare_drawing(const property_type &component)
{
	assert(component.get_pointer());
	drawing_instruction_collection instructions;
	component->render(instructions);
	for (const auto &instr : instructions)
	{
		const uint64_t id = instr.id;
		assert(instr.points.size() > 0);
		int32_t draw_type;

		switch (instr.points.size())
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

		shape to_add{instr, component};
		to_add.property.set_flag(shape::IS_DYNAMIC, component.get_flag(shape::IS_DYNAMIC));

		auto found = objects.find(draw_type);
		if (found != objects.end()) // if found
		{
			auto it = found->second.lower_bound(shape{instr, component}); // get range of theese which points to currently processed component

			if (id != it->get_id()) // add fresh points
			{
				objects[draw_type].emplace(to_add);
			}
			else // update existing ones
			{
				while (it != found->second.end() && it->get_id() == id)
				{
					it->instr.points = instr.points;
					it->instr.color = instr.color;
					it++;
				}
			}
		}
		else
			objects[draw_type] = list_of_shapes{to_add};
	}
}

void Window::display()
{
	// auto lamda = get_async_lambda();

	// update dynamic components while static ones will be processed
	// std::future<bool> ready = std::async(std::launch::async, [&]() { return lamda(*this); });

	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, get_window_width(), get_window_height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-1, 1, -1, 1, -1, 1);

	auto render_objects = [&](const bool dynamic) {
		//iterate over categories of primitives
		for (const auto &var : objects)
		{
			// iterate to beginning of dynamic range
			auto it = var.second.begin();
			while (it != var.second.end() && it->property.get_flag(shape::IS_DYNAMIC) != dynamic)
				it++;

			// start rendering this category
			glBegin(var.first);

			// iterate as long as range and filter is kept
			while (it != var.second.end() && it->property.get_flag(shape::IS_DYNAMIC) == dynamic)
			{
				// get color once instead of four
				const Color tmp_color{it->instr.color};

				// paint
				glColor4d(tmp_color.r, tmp_color.g, tmp_color.b, tmp_color.a);

				// clue - render shape
				for (const point &pnt : it->instr.points)
					glVertex2d(pnt.x, pnt.y);

				it->instr.additional_instructions();

				it++;
			}

			// stop rendering
			glEnd();
		}
	};

	// render static objects
	render_objects(false);

	// wait for end of processing
	for (const auto &comp : components)
	{
		if (comp.get_flag(shape::IS_DYNAMIC) && comp->move())
			prepare_drawing(comp);
	}

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
	{
		prepare_drawing(comp);
	}
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

void Window::add_component(Component *cmp, const bool is_dynamic)
{
	assert(cmp);
	component_type tmp{cmp};
	if (is_dynamic)
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
		{
			if (comp.get_flag(shape::IS_DYNAMIC) && comp->move())
				wnd.prepare_drawing(comp);
		}
		return true;
	};
}

Window::~Window()
{
	objects.clear();
	for (component_type &cmp : components)
	{
		Component *tmp = cmp.get_pointer();
		if (tmp != nullptr)
		{
			delete tmp;
			tmp = nullptr;
		}
	}
	components.clear();
}

void Window::window_size_changed()
{
	for (auto &var : components)
		var->resize();
}