#include <GL/glut.h>

#include <cassert>
#include <functional>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std::chrono_literals;

using num = double;
using point = std::pair<num, num>;
using points_collection = std::vector<point>;
using draw_function = std::function<void(const points_collection &)>;

struct color
{
	double r, g, b, a;
};

void draw(const color &c, const points_collection &points)
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

	glBegin(draw_type);
	glColor4f(c.r, c.g, c.b, c.a);
	// glLineWidth(1.0);
	for (const point &p : points)
		glVertex2f(p.first, p.second);
	glEnd();
}

void display()
{
	double pos = -1.0;
	double mod = 0.01;
	while(true)
	{
		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		double y;

		if(mod > 0.0)
			y = std::sqrt(1.0 - (pos*pos));
		else
			y= -std::sqrt(1.0 - (pos*pos));


		// draw({0, 1.0, 0, 0.5}, {{{-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5}}});
		draw({0, 1.0, 0, 0.5}, {{-1.0, 0.0}, { pos, y}, {1.0, 0.0}});
		glFlush();
		pos += mod;
		std::this_thread::sleep_for(5ms);
		if(pos >= 1.0 || pos <= -1.0) mod *= -1.0;
		// if(pos >= 1.0) pos = -1.0;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("WHOA TROJKAT KURWA");
	
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}