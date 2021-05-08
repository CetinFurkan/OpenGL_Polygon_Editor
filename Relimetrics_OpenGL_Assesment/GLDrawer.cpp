#include "GLDrawer.h"

GLDrawer::GLDrawer()
{
	listColor[0] = { 255,255,255  ,255 }; //COLOR_WHITE = 0,
	listColor[1] = { 0  ,0  ,0    ,255 }; //COLOR_BLACK = 1,
	listColor[2] = { 255,0  ,0    ,255 }; //COLOR_RED = 2,
	listColor[3] = { 0  ,0  ,255  ,255 }; //COLOR_BLUE = 3,
	listColor[4] = { 0  ,255,0    ,255 }; //COLOR_GREEN = 4,
	listColor[5] = { 255,255,0    ,255 }; //COLOR_YELLOW = 5,
	listColor[6] = { 205,130,0    ,255 }; //COLOR_ORANGE = 6,
	listColor[7] = { 0  ,255,255  ,255 }; //COLOR_AQUA = 7,
}

GLDrawer::~GLDrawer()
{

}


void GLDrawer::drawLine(Point* _p0, Point* _p1, ColorType _col, int _t)
{
	glColorRGB(listColor[_col].r, listColor[_col].g, listColor[_col].b);
	glLineWidth(_t);

	glBegin(GL_LINES);

	glVertex2f(_p0->getX(), _p0->getY());
	glVertex2f(_p1->getX(), _p1->getY());

	glEnd();

	glLineWidth(1);
}


void GLDrawer::drawPolygon(Polygonic *_p, ColorType _col, int _t)
{
	glColorRGB(listColor[_col].r, listColor[_col].g, listColor[_col].b);
	glLineWidth(_t);

	glBegin(GL_LINES);
	for (uint8_t i = 1; i < _p->listPoint.size(); i++)
	{
		glVertex2f(_p->listPoint[i]->getX(), _p->listPoint[i]->getY());
		glVertex2f(_p->listPoint[i - 1]->getX(), _p->listPoint[i - 1]->getY());
	}
	glEnd();

	glLineWidth(1);
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

int GLDrawer::getSnappedGridValueX(float _x)
{
	return floor((_x + gridSize / 2.0) / gridSize)*gridSize;
}

int GLDrawer::getSnappedGridValueY(float _y)
{
	return floor((_y+ gridSize/2.0) / gridSize)*gridSize;
}

bool GLDrawer::isPointInsideOfCanvas(Point *_p)
{
	return isInsidePointInRect(_p, 0,0,canvasWidth,canvasHeight);
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