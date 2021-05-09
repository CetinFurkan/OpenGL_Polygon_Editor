#include "GLDrawer.h"

//Singleton
GLDrawer* GLDrawer::instance = 0;

GLDrawer* GLDrawer::getInstance()
{
	if (instance == 0)
	{
		instance = new GLDrawer();
	}

	return instance;
}

GLDrawer::GLDrawer()
{
	initColors();
}


void GLDrawer::initColors()
{
	listColor[0] = { 255,255,255 }; //COLOR_WHITE = 0,
	listColor[1] = { 0  ,0  ,0 };   //COLOR_BLACK = 1,
	listColor[2] = { 255,0  ,0 };   //COLOR_RED = 2,
	listColor[3] = { 0  ,0  ,255 }; //COLOR_BLUE = 3,
	listColor[4] = { 0  ,255,0 };   //COLOR_GREEN = 4,
	listColor[5] = { 255,255,0 };   //COLOR_YELLOW = 5,
	listColor[6] = { 205,130,0 };   //COLOR_ORANGE = 6,
	listColor[7] = { 0  ,255,255 }; //COLOR_AQUA = 7,
}


void GLDrawer::drawLine(Point _p0, Point _p1, ColorType _col, int _t)
{
	glColorRGB(listColor[_col].r, listColor[_col].g, listColor[_col].b);
	glLineWidth(_t);

	glBegin(GL_LINES);

	glVertex2f(_p0.x, _p0.y);
	glVertex2f(_p1.x, _p1.y);

	glEnd();

	glLineWidth(1);
}

//Main Polygon drawing function 
void GLDrawer::drawPolygon(PolygonParent *_p, ColorType _col)
{
	if (activeRenderType == RENDER_POLYGON) {  //Draw Filled Polygon first, so that it remains at bottom when drawing on screen 
		glBegin(GL_TRIANGLE_FAN);
		glColorRGB(listColor[_col].r, listColor[_col].g, listColor[_col].b);
		for (uint8_t i = 2; i < _p->getSize(); i++)
		{
			glVertex2f(_p->getPoint(0).x, _p->getPoint(0).y);
			glVertex2f(_p->getPoint(i).x, _p->getPoint(i).y);
			glVertex2f(_p->getPoint(i - 1).x, _p->getPoint(i - 1).y);
		}
		glEnd();
	}

	if (activeRenderType == RENDER_POLYGON || activeRenderType == RENDER_LINES) { //Lines are drawn (it here is polygon, lines are darawn onto them 
		glBegin(GL_LINES);

		if (activeRenderType == RENDER_POLYGON)
			glColorRGB(255,255,255);
		else
			glColorRGB(listColor[_col].r, listColor[_col].g, listColor[_col].b);

		glLineWidth(3);
		for (uint8_t i = 1; i < _p->getSize(); i++)
		{
			glVertex2f(_p->getPoint(i).x, _p->getPoint(i).y);
			glVertex2f(_p->getPoint(i-1).x, _p->getPoint(i-1).y);

			glVertex2f(_p->getPoint(i).x, _p->getPoint(i).y);
			glVertex2f(_p->getPoint(0).x, _p->getPoint(0).y);
		}
		glLineWidth(1);
		glEnd();
	}

	if (activeRenderType == RENDER_POINTS) {//Draws small points at each point data
		glBegin(GL_POINTS);
		glColorRGB(255,255,255);
		glPointSize(15.0);
		for (uint8_t i = 0; i < _p->getSize(); i++)
		{
			glVertex2f(_p->getPoint(i).x, _p->getPoint(i).y);
		}
		glPointSize(1);
		glEnd();
	}

	glFlush();
}


void GLDrawer::setCanvasPorperties(int _cw, int _ch, int _gridsize)
{
	canvasWidth = _cw;
	canvasHeight = _ch;
	gridSize = _gridsize;
}

int GLDrawer::getSnappedGridValueX(float _x)
{
	if (!isGridActive)
		return _x;

	return floor((_x + gridSize / 2.0) / gridSize)*gridSize;
}

int GLDrawer::getSnappedGridValueY(float _y)
{
	if (!isGridActive)
		return _y;

	return floor((_y + gridSize / 2.0) / gridSize)*gridSize;
}

bool GLDrawer::isPointInsideOfCanvas(Point _p)
{
	if (!isGridActive)
		return true;

	return isInsidePointInRect(_p, 0, 0, canvasWidth, canvasHeight);
}

void GLDrawer::setRenderingMode(RenderTypes _render)
{
	activeRenderType = _render;
}

void GLDrawer::switchGridOnOff()
{
	isGridActive = !isGridActive;
}

//Basic drawing function
void GLDrawer::drawCanvasWithGrid() {

	if (isGridActive == false)
		return;

	glColorRGB(30, 30, 30);

	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0 + canvasWidth, 0);
	glVertex2f(0 + canvasWidth, 0 + canvasHeight);
	glVertex2f(0, 0 + canvasHeight);
	glEnd();

	glColorRGB(140, 140, 140);
	glPointSize(1.0);

	glBegin(GL_POINTS);

	for (int i = 0; i <= (canvasWidth / gridSize); i++)
		for (int j = 0; j <= (canvasHeight / gridSize); j++) {
			glVertex2f(i*gridSize, j*gridSize);
		}

	glEnd();
	//glFlush();

}