#include "window.h"
#include <thread>
#include <future>
#include "../button/button.h"

void Window::prepare_drawing(const color &c, const component *component, prepared_objects &dst)
{
	assert(component);
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

		auto found = dst.find(draw_type);
		if (found != dst.end()) // if found
		{
			auto ret_pair = found->second.insert(shape{c, points, ptr_to_int(component)});
			if (!ret_pair.second) // update
			{
				if (c != color{0.0, 0.0, 0.0, 0.0})
					ret_pair.first->colour = c;
				ret_pair.first->points = points;
			}
		}
		else
			dst.insert(dst.end(), {draw_type, {shape{c, points, ptr_to_int(component)}}});
	}
}

void Window::display()
{
	// update components
	std::future<bool> ready = std::async(std::launch::async, [&]() -> bool {
		for (component *cmp : objects)
			if (cmp->move())
				this->prepare_drawing({0.0, 0.0, 0.0, 0.0}, cmp, prepared_dynamic_objects);

		return true;
	});

	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, get_window_width(), get_window_height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-1,1,-1,1, -1,1);

	// render static objects (fast)
	for (const auto &var : prepared_static_objects)
	{
		glBegin(var.first);
		for (const shape &sh : var.second)
		{
			glColor4d(sh.colour.r, sh.colour.g, sh.colour.b, sh.colour.a);
			for (const point &pnt : sh.points)
				glVertex2d(pnt.x, pnt.y);
		}
		glEnd();
	}

	// render dynamic objects (slower)
	ready.wait();
	for (const auto &var : prepared_dynamic_objects)
	{
		glBegin(var.first);
		for (const shape &sh : var.second)
		{
			glColor4d(sh.colour.r, sh.colour.g, sh.colour.b, sh.colour.a);
			for (const point &pnt : sh.points)
				glVertex2d(pnt.x, pnt.y);
		}
		glEnd();
	}

	glFlush();
}

Window::~Window()
{
	for (component *ptr : objects)
	{
		delete ptr;
		ptr = nullptr;
	}

	objects.clear();
}
Window::Window(const std::string &str, int *argc, char **argv)
{
	glutInit(argc, argv);
	glutInitWindowSize(get_window_width(), get_window_height());
	glutCreateWindow(str.c_str());
}

void Window::prepare_static()
{
	for (component *cmp : objects)
		this->prepare_drawing({0.0, 0.0, 0.0, 0.0}, cmp, prepared_dynamic_objects);
}

void Window::on_click(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			// clicks
			const Point clip{to_number(x), to_number(y), SCREEN};
			for (component *ptr : objects)
				if (Clickable *btn = dynamic_cast<Clickable *>(ptr))
				{
					if (btn->click(clip))
						break;
				}

			// hold down (TODO)
		}
		else if (state == GLUT_UP)
		{
			// hold up (TODO)
		}
	}
}
