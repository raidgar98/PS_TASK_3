#include <GL/glut.h>

#include <cassert>
#include <functional>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <cstring>
#include <memory>

#include "libraries/engine/SwitcherEngine.hpp"
#include "libraries/graphic/Point.h"
#include "button.h"

using namespace std::chrono_literals;

using point = Point;
using point_ptr = std::shared_ptr<point>;
using points_collection = std::vector<point>;

inline auto get_poin_ptr(const number x, const number y) { return std::make_shared<point>(x, y); }

struct color
{
	double r, g, b, a;
};

void button1_onClick_event();
void button2_onClick_event();
void button3_onClick_event();
void draw(const color &c, const points_collection &points);
void display();
void OnMouseClick(int button, int state, int x, int y);

int main(int argc, char **argv)
{
	SwitcherEngine<5> eng; // added just for tests
	glutInit(&argc, argv);
	glutInitWindowSize(300, 500);
	//glutInitWindowPosition(50, 50);
	glutCreateWindow("APP");
	glutDisplayFunc(display);
	glutMouseFunc(OnMouseClick);
	glutMainLoop();
	return 0;
}

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
	glColor3d(c.r, c.g, c.b);
	// glLineWidth(1.0);
	for (const point &p : points)
		glVertex2d(p.x, p.y);
	glEnd();
}

void display()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// For 4x4 grid
	static int NUMBER_OF_FIELDS = 4;

	draw(
		{0.2, 0.2, 0.2, 1.0},
		{{0.9, 0.9},
		 {-0.9, 0.9},
		 {-0.9, -0.3},
		 {0.9, -0.3}});

	draw(
		{0.0, 1.0, 0.0, 1.0},
		{{0.9, -0.4},
		 {-0.9, -0.4},
		 {-0.9, -0.9},
		 {0.9, -0.9}});
	number wSpace = 0.02;
	number hSpace = 0.02;
	number hPlace = 0.1333;
	number wPlace = 0.2;
	number hField = hPlace / (NUMBER_OF_FIELDS / 10.0) - ((hPlace + (3 * hSpace)) / NUMBER_OF_FIELDS);
	number wField = ((wPlace) / (NUMBER_OF_FIELDS / 10.0)) - ((wPlace + (3 * wSpace)) / NUMBER_OF_FIELDS);
	number xMoveCalc = wSpace + wField;
	number yMoveCalc = hSpace + hField;

	point_ptr b = get_poin_ptr(-0.9, 0.9);
	point_ptr a = get_poin_ptr(b->x + wField, b->y);
	point_ptr c = get_poin_ptr(b->x, b->y - hField);
	point_ptr d = get_poin_ptr(a->x, c->y);

	for (int i = 0; i < NUMBER_OF_FIELDS; ++i)
	{
		number xMove = i * xMoveCalc;
		for (int j = 0; j < NUMBER_OF_FIELDS; ++j)
		{
			number yMove = j * yMoveCalc;
			draw(
				{1.0f - (j / 10.0), 1.0, 1.0 - (i / 10.0)},
				{
					{a->x + xMove, a->y - yMove},
					{b->x + xMove, b->y - yMove},
					{c->x + xMove, c->y - yMove},
					{d->x + xMove, d->y - yMove},
				});
		}
	}

	// draw buttons
	draw(
		{0.0, 0.0, 0.0, 1.0},
		{{-0.3, -0.65},
		 {-0.9, -0.65},
		 {-0.9, -0.9},
		 {-0.3, -0.9}});

	draw(
		{0.0, 0.0, 0.1, 1.0},
		{{-0.3+0.6, -0.65},
		 {-0.9+0.6, -0.65},
		 {-0.9+0.6, -0.9},
		 {-0.3+0.6, -0.9}});

	draw(
		{0.0, 0.0, 0.2, 1.0},
		{{-0.3+1.2, -0.65},
		 {-0.9+1.2, -0.65},
		 {-0.9+1.2, -0.9},
		 {-0.3+1.2, -0.9}});

	glFlush();
}

void OnMouseClick(int button, int state, int x, int y)
{
	// From pixels to opengl's xy
	float xClip = ((x + 0.5f) / 300.0f) * 2.0f - 1.0f;
	float yClip = 1.0f - ((y + 0.5f) / 500.0f) * 2.0f;

  	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
  	{ 
	  	Button button1(-0.65,-0.9,0.6,-0.25,button1_onClick_event);
	  	button1.CheckClick(xClip, yClip);

	  	Button button2(-0.65,-0.9+0.6,0.6,-0.25,button2_onClick_event);
	  	button2.CheckClick(xClip, yClip);

	  	Button button3(-0.65,-0.9+1.2,0.6,-0.25,button3_onClick_event);
	  	button3.CheckClick(xClip, yClip);
  	}	
}

void button1_onClick_event(){
	std::cout<<"Button1 Click"<<std::endl;
}

void button2_onClick_event(){
	std::cout<<"Button2 Click"<<std::endl;
}

void button3_onClick_event(){
	std::cout<<"Button3 Click"<<std::endl;
}