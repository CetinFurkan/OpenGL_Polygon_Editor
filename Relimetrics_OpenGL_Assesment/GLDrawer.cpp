#include "GLDrawer.h"

GLDrawer::GLDrawer()
{

}

GLDrawer::~GLDrawer()
{

}


void GLDrawer::drawPolygon(Polygonic *_p)
{
	//TODO:implement 
}

void GLDrawer::setCanvasPorperties(int _cw, int _ch, int _gridsize, GridType _gridtype)
{
	canvasWidth = _cw;
	canvasHeight = _ch;
	gridSize = _gridsize;
	gridType = GRID_TYPE_SQUARE;
}

void GLDrawer::setCanvasType(GridType _gridtype)
{
	gridType = _gridtype;
}


void GLDrawer::drawRectFilled(float _x, float _y, float _w, float _h)
{
	glBegin(GL_POLYGON);
	glVertex2f(_x, _y);
	glVertex2f(_x + _w, _y);
	glVertex2f(_x + _w, _y + _h);
	glVertex2f(_x, _y + _h);
	glEnd();

	glFlush();
}
void GLDrawer::drawSquareGrid(float _x, float _y, int _w, int _h, float _size, float _t) {
	glBegin(GL_LINES);

	for (uint8_t i = 0; i <= (_w / _size); i++)
	{
		glVertex2f(_x + i * _size, _y);
		glVertex2f(_x + i * _size, _y + _h);
	}

	glEnd();

	glBegin(GL_LINES);

	for (uint8_t i = 0; i <= (_h / _size); i++)
	{
		glVertex2f(_x, _y + i * _size);
		glVertex2f(_x + _w, _y + i * _size);
	}

	glEnd();
}
void GLDrawer::drawPointGrid(float _x, float _y, int _w, int _h, float _size, float _t) {
	glBegin(GL_POINTS);

	for (uint8_t i = 0; i <= (_w / _size); i++)
		for (uint8_t j = 0; j <= (_h / _size); j++) {
			glVertex2f(_x, _y);
		}

	glEnd();
}


void GLDrawer::drawCanvasWithGrid() {

	glColorRGB(30, 30, 30);
	drawRectFilled(0, 0, canvasWidth, canvasHeight);

	glColorRGB(140, 140, 140);
	if (gridType == GRID_TYPE_SQUARE) {
		drawSquareGrid(0, 0, canvasWidth, canvasHeight, gridSize, 1);
	}
	else if (gridType == GRID_TYPE_POINTS) {
		drawPointGrid(0, 0, canvasWidth, canvasHeight, gridSize, 2);
	}
	else if (gridType == GRID_TYPE_SQUARE_POINTS) {
		drawPointGrid(0, 0, canvasWidth, canvasHeight, gridSize, 2);
		drawSquareGrid(0, 0, canvasWidth, canvasHeight, gridSize, 1);
	}
	else if (gridType == GRID_TYPE_SQUARE_DOUBLE) {
		drawSquareGrid(0, 0, canvasWidth, canvasHeight, gridSize, 2);
		drawSquareGrid(0, 0, canvasWidth, canvasHeight, gridSize / 2, 1);
	}

	glFlush();
}