#pragma once
#include "Common.h"

#ifndef GLDRAWER_H
#define GLDRAWER_H

#define COLOR_WHITE  0
#define COLOR_BLACK  1
#define COLOR_RED    2
#define COLOR_BLUE   3
#define COLOR_GREEN  4
#define COLOR_YELLOW 5
#define COLOR_ORANGE 6
#define COLOR_AQUA   7

class GLDrawer
{
	GLDrawer();
	~GLDrawer();

public:
	void drawPolygon(Polygonic*);

};


static void glColorRGB(GLfloat _r, GLfloat _g, GLfloat _b) {
	glColor3f(_r / 255.0f, _g / 255.0f, _b / 255.0f);
}

static void glColorRGB(Color *_color) {
	glColor3f(_color->getR() / 255.0f, _color->getG() / 255.0f, _color->getB() / 255.0f);
}


#endif GLDRAWER_H