#include "window.h"
#include <thread>
#include <future>
#include <iostream>
#include "../button/button.h"
#include "../drag_n_drop/drag_n_drop.h"

void Window::display()
{
	// auto lamda = get_async_lambda();

	// update dynamic components while static ones will be processed
	// std::future<bool> ready = std::async(std::launch::async, [&]() { return lamda(*this); });

	// DEBUG
	for (component_type c : components)
		std::cout << c->id << "( " << dynamic_cast<DragAndDrop *>(c.get_pointer())->get_child()->id << " )" << std::endl;

	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, get_window_width(), get_window_height());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	//iterate over categories of primitives
	for (const auto &rend : {GL_POINT, GL_LINE, GL_TRIANGLES, GL_QUADS, GL_POLYGON})
	{
		// start of rendering
		glBegin(rend);
		for(const component_type& c : components)
		{
			std::cout << "rendering: "<< c->name() << std::endl;
			const auto& found = c->shapes().find(rend);
			if(found == c->shapes().end()) continue;
			for(const drawing_instruction& instr : found->second)
			{
				glColor4d(instr.color.r, instr.color.g, instr.color.b, instr.color.a);

				// clue - render shape
				for (const point &pnt : instr.points)
					glVertex2d(pnt.x, pnt.y);

				instr.additional_instructions();
			}
		}
		// stop rendering
		glEnd();
	}

	// additional render instructions
	for (component_type &prop : components)
		prop->additional_render_instruction();

	// push to screen
	glFlush();
}

Window::Window(const std::string &str, int *argc, char **argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(get_window_width(), get_window_height());
	glutCreateWindow(str.c_str());
}

void Window::preprocess_components()
{
	for (const component_type &comp : components)
		comp->render();
}

void Window::on_click(int button, int state, int x, int y)
{
	const Point clip{to_number(x), to_number(y), SCREEN};
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			for (component_type &ptr : components)
				if (DragAndDrop *dnd = dynamic_cast<DragAndDrop *>(ptr.get_pointer()))
					if (dnd->hit(clip))
					{
						std::cout << "drag detect" << std::endl;
						drag.set_pointer(dnd);
						dnd->drag(clip);
						preprocess_components();
						display(); // refresh
						return;
					}
		}
		else if (state == GLUT_UP)
		{
			for (component_type &ptr : components)
			{
				if (Clickable *btn = dynamic_cast<Clickable *>(ptr.get_pointer()))
				{
					if (btn->hit(clip))
					{
						if (btn == drag.get_pointer())
						{
							std::cout << "click detect" << std::endl;
							dynamic_cast<DragAndDrop *>(drag.get_pointer())->drop(nullptr);
							drag.set_pointer(nullptr);
							btn->click(clip);
							display();
							return;
						}
						else if (drag.get_pointer() != nullptr)
						{
							if (DragAndDrop *dnd = dynamic_cast<DragAndDrop *>(ptr.get_pointer()))
							{
								std::cout << "drop detect" << std::endl;
								dynamic_cast<DragAndDrop *>(drag.get_pointer())->drop(dnd);
								// dnd->drop(*dynamic_cast<DragAndDrop *>(drag.get_pointer()));
								drag.set_pointer(nullptr);
								display(); // refresh
								return;
							}
						}
						std::cout << "wild click detect" << std::endl;
						btn->click(clip);
						return;
					}
				}
			}

			if (drag.get_pointer() != nullptr)
			{
				std::cout << "wild drop detect" << std::endl;
				dynamic_cast<DragAndDrop *>(drag.get_pointer())->drop(nullptr);
				drag.set_pointer(nullptr);
				display();
			}
		}
	}
}

Component *Window::add_component(Component *cmp, const bool is_dynamic)
{
	assert(cmp);
	component_type tmp{cmp};
	if (is_dynamic)
		tmp.set_flag(IS_DYNAMIC, is_dynamic);
	components.emplace_back(tmp);
	return cmp;
}

void Window::start()
{
	preprocess_components();
	glutMainLoop();
}

Window::~Window()
{
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