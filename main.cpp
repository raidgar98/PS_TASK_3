#include <GL/glut.h>

#include <cassert>
#include <functional>
#include <vector>
#include <thread>
#include <chrono>
#include <cstring>
#include <memory>
#include <iostream>

#include "libraries/graphic/components/button/button.h"
#include "textbox.h"

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
void renderBitmapString(float x, float y, void *font,const std::string string);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glutInitWindowPosition(50, 50);
	glutCreateWindow("APP");
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

	// It just numbers that show in the fields
	int counter = 1;

	for (int i = 0; i < NUMBER_OF_FIELDS; ++i)
	{
		number yMove = i * yMoveCalc;
		
		for (int j = 0; j < NUMBER_OF_FIELDS; ++j)
		{
			number xMove = j * xMoveCalc;
			draw(
				{1.0f - (j / 10.0), 1.0, 1.0 - (i / 10.0)},
				{
					{a->x + xMove, a->y - yMove},
					{b->x + xMove, b->y - yMove},
					{c->x + xMove, c->y - yMove},
					{d->x + xMove, d->y - yMove},
				});
			// For render in the middle of field
			renderBitmapString((((a->x + xMove)+(c->x + xMove))/2)-0.04, ((a->y - yMove)+(c->y - yMove))/2
				,GLUT_BITMAP_HELVETICA_18, std::to_string(counter));
			++counter;
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
		{{-0.3 + 0.6, -0.65},
		 {-0.9 + 0.6, -0.65},
		 {-0.9 + 0.6, -0.9},
		 {-0.3 + 0.6, -0.9}});

	draw(
		{0.0, 0.0, 0.2, 1.0},
		{{-0.3 + 1.2, -0.65},
		 {-0.9 + 1.2, -0.65},
		 {-0.9 + 1.2, -0.9},
		 {-0.3 + 1.2, -0.9}});
	
	// draw text "liczba ruchow"
	renderBitmapString(-0.3, ((-0.4)+(-0.65))/2
				,GLUT_BITMAP_HELVETICA_12, "Liczba ruchow: ");

	// draw textbox
	TextBox textbox({0.34,-0.46,CARTESIAN},{0.46,-0.11},"1");
	textbox.setText("2");
	glFlush();
}

void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Point Clip{ to_number(x), to_number(y), SCREEN};
		std::cout << Clip << std::endl;
		Clip = Clip.to_cartesian();
		std::cout << Clip << std::endl;

		Button button1({-0.9, -0.65, CARTESIAN}, {0.6, 0.25}, []() { std::cout << "Button1 Click"; });
		button1.CheckClick(Clip.x, Clip.y);

		Button button2({-0.3, -0.65, CARTESIAN}, {0.6, 0.25}, button2_onClick_event);
		button2.CheckClick(Clip.x, Clip.y);

		Button button3({0.3, -0.65, CARTESIAN}, {0.6, 0.25}, button3_onClick_event);
		button3.CheckClick(Clip.x, Clip.y);
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