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

enum GridType
{
	GRID_TYPE_EMPTY,
	GRID_TYPE_SQUARE,
	GRID_TYPE_POINTS,
	GRID_TYPE_SQUARE_POINTS,
	GRID_TYPE_SQUARE_DOUBLE,
	GRID_TYPE_NUMBERS,
};


//TODO: NEEDS TO BE A SINGLETON!!!
class GLDrawer
{

public:
	GLDrawer();
	~GLDrawer();

	void drawPolygon(Polygonic*, ColorType , int);
	void drawLine(Point*, Point*, ColorType, int);

	void setCanvasPorperties(int, int, int, GridType);
	void drawCanvasWithGrid();

	void setCanvasType(GridType);
	int getSnappedGridValueX(float);
	int getSnappedGridValueY(float);
	bool isPointInsideOfCanvas(Point*);

protected:
	int canvasWidth = 0;
	int canvasHeight = 0;
	int gridSize = 0;
	GridType gridType = GRID_TYPE_SQUARE;

	ColorData listColor[8];


	void drawRectFilled(float _x, float _y, float _w, float _h);
	void drawSquareGrid(float _x, float _y, int _w, int _h, float _size, float _t);
	void drawPointGrid(float _x, float _y, int _w, int _h, float _size, float _t);
};


//These functions are seperated in order to be used without GLDrawer object
static void glColorRGB(GLfloat _r, GLfloat _g, GLfloat _b) {
	glColor3f(_r / 255.0f, _g / 255.0f, _b / 255.0f);
}

static void glColorRGB(Color *_color) {
	glColor3f(_color->getR() / 255.0f, _color->getG() / 255.0f, _color->getB() / 255.0f);
}
/*
static void glColorRGB(ColorType _color) {
	return listColor[_color];

}*/


#endif GLDRAWER_H