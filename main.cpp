#include <GL/glut.h>

#include <cassert>
#include <functional>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>
#include <cstring>

#include "engine/SwitcherEngine.hpp"

using namespace std::chrono_literals;

using number = double;
using point = std::pair<number, number>;
using points_collection = std::vector<point>;
using draw_function = std::function<void(const points_collection &)>;

class Point
{
private:
	float _x;
	float _y;
public:
	Point(float x, float y): _x(x), _y(y){}
	float x(){
		return _x;
	};
	float y(){
		return _y;
	};
};

struct color { double r, g, b, a; };

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
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// For 4x4 grid
	static int NUMBER_OF_FIELDS = 4;
		
	glBegin(GL_QUADS);  	           // Each set of 4 vertices form a quad
		// Place for table's fields
		glColor3f(0.2f, 0.2f, 0.2f);
		glVertex2f(0.9f, 0.9f);     //  so that the normal (front-face) is facing you
	    glVertex2f(-0.9f, 0.9f);     // Define vertices in counter-clockwise (CCW) order
		glVertex2f(-0.9f, -0.3f);
		glVertex2f(0.9f, -0.3f);
		 
		// Place for buttons and other controls
		glColor3f(0.0f, 1.0f, 0.0f); // Green
	    glVertex2f(0.9f, -0.4f);
	    glVertex2f(-0.9f, -0.4f);
	    glVertex2f(-0.9f,  -0.9f);
	    glVertex2f(0.9f,  -0.9f);

	    // Draw each of fields
	    float wSpace = 0.02;
		float hSpace = 0.02;
		float hPlace = 0.1333;
		float wPlace = 0.2;
		float hField = hPlace/(NUMBER_OF_FIELDS/10.0)-((hPlace+(3*hSpace))/NUMBER_OF_FIELDS);
		float wField = ((wPlace)/(NUMBER_OF_FIELDS/10.0))-((wPlace+(3*wSpace))/NUMBER_OF_FIELDS);
		float xMoveCalc = wSpace+wField;
		float yMoveCalc = hSpace+hField;

		Point *b = new Point(-0.9, 0.9);
		Point *a = new Point(b->x()+wField, b->y());
		Point *c = new Point(b->x(), b->y()-hField);
		Point *d = new Point(a->x(), c->y());

	    for(int i = 0; i < NUMBER_OF_FIELDS; ++i)
	    {
	    	float xMove = i*xMoveCalc;
	    	for(int j = 0; j < NUMBER_OF_FIELDS; ++j)
	    	{
	    		float yMove = j*yMoveCalc;
	    		glColor3f(1.0f-(j/10.0f), 1.0f, 1.0f-(i/10.0f)); // blue?
			    glVertex2f(a->x()+xMove, a->y()-yMove);
			    glVertex2f(b->x()+xMove, b->y()-yMove);
			    glVertex2f(c->x()+xMove, c->y()-yMove);
			    glVertex2f(d->x()+xMove, d->y()-yMove);
	    	}
	    }

	    delete a;	    
	    delete b;	    
	    delete c;	    
	    delete d;	    
   	glEnd();

   	glColor3f( 1.0f, 0.0f, 0.0f );
		glRasterPos2f(0, 0);
		int len;
		char string[] = "Hello world";

		len = (int)strlen(string);
		for (int i = 0; i < len; i++) {
		  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, string[i]);
		}
   	glFlush();  // Render now
}

int main(int argc, char **argv)
{
	SwitcherEngine<5> eng; // added just for tests

	glutInit(&argc, argv);
	glutInitWindowSize(300,500);
	//glutInitWindowPosition(50, 50);
	glutCreateWindow("APP");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
