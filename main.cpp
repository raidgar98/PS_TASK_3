#include <cassert>
#include <thread>
#include <chrono>
#include <cstring>
#include <iostream>

#include <GL/glu.h>

#include "libraries/graphic/components/button/button.h"
#include "textbox.h"

using namespace std::chrono_literals;

inline auto get_poin_ptr(const number x, const number y) { return std::make_shared<point>(x, y); }

struct color
{
	double r, g, b, a;
};

// 3 hours of tries to avoid global variabble: https://stackoverflow.com/a/12299529 to ashes :(
std::vector< component * > draw_objects;

void button1_onClick_event();
void button2_onClick_event();
void button3_onClick_event();
void draw(const color &c, const points_collection &points);
void display();
void OnMouseClick(int button, int state, int x, int y);
void renderBitmapString(float x, float y, void *font,const std::string string);

void init_draw_objects()
{
	draw_objects = {
		new Button({-0.9, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, []() { std::cout << "Button1 Click" << std::endl; }),
		new Button({-0.3, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, []() { std::cout << "Button2 Click" << std::endl; }),
		new Button({0.3, -0.65, CARTESIAN}, {0.3, 0.2, CARTESIAN}, []() { std::cout << "Button3 Click" << std::endl; })
	};
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	init_draw_objects();
	glutInitWindowSize(get_window_width(), get_window_height());
	glutCreateWindow("APP");
	// glutDisplayFunc([&](){  });
	glutDisplayFunc(display);
	glutMouseFunc(OnMouseClick);
	//std::cout<<font_t[1];
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
void renderBitmapString(float x, float y, void *font,const std::string string){
    const char *c;
    glColor3d(0.0, 0.0,0.0);
    glRasterPos2f(x, y);
    for (c=string.c_str(); *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
} 

void display()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glViewport(0,0,get_window_width(),get_window_height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1,1,-1,1, -1,1);

	// // For 4x4 grid
	// static int NUMBER_OF_FIELDS = 4;

	// draw(
	// 	{0.2, 0.2, 0.2, 1.0},
	// 	{{0.9, 0.9},
	// 	 {-0.9, 0.9},
	// 	 {-0.9, -0.3},
	// 	 {0.9, -0.3}});

	// draw(
	// 	{0.0, 1.0, 0.0, 1.0},
	// 	{{0.9, -0.4},
	// 	 {-0.9, -0.4},
	// 	 {-0.9, -0.9},
	// 	 {0.9, -0.9}});
	// number wSpace = 0.02;
	// number hSpace = 0.02;
	// number hPlace = 0.1333;
	// number wPlace = 0.2;
	// number hField = hPlace / (NUMBER_OF_FIELDS / 10.0) - ((hPlace + (3 * hSpace)) / NUMBER_OF_FIELDS);
	// number wField = ((wPlace) / (NUMBER_OF_FIELDS / 10.0)) - ((wPlace + (3 * wSpace)) / NUMBER_OF_FIELDS);
	// number xMoveCalc = wSpace + wField;
	// number yMoveCalc = hSpace + hField;

	// point_ptr b = get_poin_ptr(-0.9, 0.9);
	// point_ptr a = get_poin_ptr(b->x + wField, b->y);
	// point_ptr c = get_poin_ptr(b->x, b->y - hField);
	// point_ptr d = get_poin_ptr(a->x, c->y);

	// for (int i = 0; i < NUMBER_OF_FIELDS; ++i)
	// {
	// 	number xMove = i * xMoveCalc;
	// 	for (int j = 0; j < NUMBER_OF_FIELDS; ++j)
	// 	{
	// 		number yMove = j * yMoveCalc;
	// 		draw(
	// 			{1.0f - (j / 10.0), 1.0, 1.0 - (i / 10.0)},
	// 			{
	// 				{a->x + xMove, a->y - yMove},
	// 				{b->x + xMove, b->y - yMove},
	// 				{c->x + xMove, c->y - yMove},
	// 				{d->x + xMove, d->y - yMove},
	// 			});
	// 	}
	// }

	for( const auto& ptr : draw_objects )
	{
		const auto render = ptr->render();
		for(const auto& obj : render)
			draw( {0.0, 0.0, 0.1, 1.0}, obj );
	}

	glFlush();
}

void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		const Point clip{to_number(x), to_number(y), SCREEN};
		for(const component* ptr : draw_objects)
			if( const Button* btn = dynamic_cast<const Button*>(ptr) )
			{
				if(btn->CheckClick( clip ))
					break;
			}
	}
}

void button2_onClick_event()
{
	std::cout << "Button2 Click" << std::endl;
}

void button3_onClick_event()
{
	std::cout << "Button3 Click" << std::endl;
}