#pragma once

#include <GL/glut.h>
#include <functional>
#include "libraries/graphic/include/Dimension.h"
#include "libraries/graphic/include/Point.h"

class TextBox
{
public:

  Point point;
  Dimension dimensions;
  std::string text;

  TextBox(const Point _point, const Dimension _dim, const std::string _text)
      : point{_point}, dimensions{ _dim }, text{ _text } {
        drawBox();
      }

  ~TextBox() {}
    
  void drawBox(){
    // Frame of box
    glBegin(GL_QUADS);
    glColor3d(0.0, 0.0, 0.0);
    glVertex2d(point.x+dimensions.width, point.y);
    glVertex2d(point.x, point.y);
    glVertex2d(point.x, point.y+dimensions.height);
    glVertex2d(point.x+dimensions.width, point.y+dimensions.height);
    glEnd();
    glBegin(GL_QUADS);
    // Inside background of box
    glColor3d(1.0, 1.0, 0.8);
    glVertex2d(point.x+dimensions.width-0.01, point.y-0.01);
    glVertex2d(point.x+0.01, point.y-0.01);
    glVertex2d(point.x+0.01, point.y+dimensions.height+0.01);
    glVertex2d(point.x+dimensions.width-0.01, point.y+dimensions.height+0.01);
    glEnd();
    // Render text in box
    const char *c;
    glColor3d(0.0, 0.0,0.0);
    glRasterPos2f(point.x+0.04, ((point.y-0.02)
      +(point.y+dimensions.height))/2);
    for (c=text.c_str(); *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
  }

  void setText(std::string _text){
    text = _text;
    drawBox();
  }
};