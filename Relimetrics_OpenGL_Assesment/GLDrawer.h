#pragma once
#include "Common.h"

#ifndef GLDRAWER_H
#define GLDRAWER_H


enum ColorType
{
	COLOR_WHITE = 0,
	COLOR_BLACK = 1,
	COLOR_RED = 2,
	COLOR_BLUE = 3,
	COLOR_GREEN = 4,
	COLOR_YELLOW = 5,
	COLOR_ORANGE = 6,
	COLOR_AQUA = 7,
};

enum RenderTypes
{
	RENDER_POINTS,
	RENDER_LINES,
	RENDER_POLYGON,
};

struct ColorData {
	GLubyte r = 0;
	GLubyte g = 0;
	GLubyte b = 0;
};

//TODO: NEEDS TO BE A SINGLETON!!!
class GLDrawer
{

public:
	GLDrawer();
	~GLDrawer();

	void drawPolygon(Polygonic*, ColorType , uint8_t);
	void drawLine(Point*, Point*, ColorType, int);

	void setCanvasPorperties(int, int, int);
	void drawCanvasWithGrid();

	void setCanvasType();
	int getSnappedGridValueX(float);
	int getSnappedGridValueY(float);
	bool isPointInsideOfCanvas(Point*);

	void setRenderingMode(RenderTypes);
	void switchGridOnOff();

protected:
	bool isGridActive = true;

	int canvasWidth = 0;
	int canvasHeight = 0;
	int gridSize = 0;

	RenderTypes activeRenderType = RENDER_POLYGON;

	ColorData listColor[8];
	
};


//These functions are seperated in order to be used without GLDrawer object
static void glColorRGB(GLfloat _r, GLfloat _g, GLfloat _b) {
	glColor3f(_r / 255.0f, _g / 255.0f, _b / 255.0f);
}

static void glColorRGB(ColorData _color) {
	glColor3f(_color.r / 255.0f, _color.g / 255.0f, _color.b / 255.0f);
}



/*
static void glColorRGB(ColorType _color) {
	return listColor[_color];

}*/


#endif GLDRAWER_H