/*
 * Relimetrics_OpenGL_Assesment - v1.0.0
 *
 * Created by Furkan Cetin (09/05/2021)
 *
 */

#include <windows.h>  
#include "Common.h"
#include "GLDrawer.h"

 ////////////////////////////////////////////////
//You can edit Canvas properties here!!!
#define CANVAS_WIDTH     1600
#define CANVAS_HEIGHT    1200
#define CANVAS_GRID_SIZE    8
////////////////////////////////////////////////

//Needed for panning around
enum Directions
{
	DIR_RIGHT,
	DIR_UP,
	DIR_LEFT,
	DIR_DOWN,
};

GLint windowWidth = 1200, windowHeight = 800;

float zoom = 1.0f;
float zoomTarget = 1.5f;

Point viewPort;
Point viewPortTarget;
Point pointMousePressed;
Point pointMouseOnCanvas;
Point pointMouseOnCanvasSnappedToGrid;
Point pointLastAdded;

GLDrawer* glDrawer;

bool isDrawingMode = false;

bool isPressingMouseButton = false;
bool isMouseInsideCanvas = false;
bool isControlKeyPressed = false;

vector<PolygonArray*> polygonList;
PolygonVector* polygonDrawn;

static void setDrawingMode(bool _mode)
{
	if (isDrawingMode == true && _mode == false)
		glutSetCursor(GLUT_CURSOR_INHERIT);

	if (isDrawingMode == false && _mode == true)
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	isDrawingMode = _mode;
}

static void funcInit() {
	viewPort = { 0.0f , 0.0f };
	viewPortTarget = { -1.0f , 1.0f };

	pointMousePressed = { 0.0f , 0.0f };
	pointMouseOnCanvas = { 0.0f , 0.0f };
	pointMouseOnCanvasSnappedToGrid = { 0.0f , 0.0f };

	pointLastAdded = { -1.0f , -1.0f };

	polygonDrawn = new PolygonVector();

	glDrawer = GLDrawer::getInstance();
	glDrawer->setCanvasPorperties(CANVAS_WIDTH, CANVAS_HEIGHT, CANVAS_GRID_SIZE);
}

static void funcReshape(int _width, int _height)
{
	windowWidth = _width;
	windowHeight = _height;
	glViewport(0, 0, windowWidth, windowHeight);
}

void panScreen(Directions _dir, float _amount) {
	cout << _dir;

	if (_dir == DIR_LEFT) {
		viewPortTarget.x += (_amount * (1.0f / windowWidth));
	}
	else if (_dir == DIR_RIGHT) {
		viewPortTarget.x -= (_amount * (1.0f / windowWidth));
	}

	if (_dir == DIR_UP) {
		viewPortTarget.y -= (_amount * (1.0f / windowHeight));
	}
	else if (_dir == DIR_DOWN) {
		viewPortTarget.y += (_amount * (1.0f / windowHeight));
	}
}

static void funcSpecialKeyUp(int _key, int _x, int _y)
{
	//if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
	//	isControlKeyPressed = false;
}

static void funcSpecialKey(int _key, int _x, int _y)
{
	if (_key == GLUT_KEY_F1)
		glDrawer->setRenderingMode(RENDER_POINTS);
	else if (_key == GLUT_KEY_F2)
		glDrawer->setRenderingMode(RENDER_LINES);
	else if (_key == GLUT_KEY_F3)
		glDrawer->setRenderingMode(RENDER_POLYGON);

	/* Optional Use for panning on screen
	if (_key == GLUT_KEY_LEFT)
		panScreen(DIR_LEFT, 40);
	else if (_key == GLUT_KEY_RIGHT)
		panScreen(DIR_RIGHT, 40);

	if (_key == GLUT_KEY_UP)
		panScreen(DIR_UP, 40);
	else if (_key == GLUT_KEY_DOWN)
		panScreen(DIR_DOWN, 40);
	*/


	//Detection CTRL is not working
	//if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
	//	isControlKeyPressed = true;
}

void funcIdle()
{
	glutPostRedisplay();
}


static void funcKey(unsigned char _key, int x, int y)
{
	//Pan Screen by changing viewPortTarget
	viewPortTarget.x += ((_key == 'a' || _key == 'A') * 36 * (1.0f / windowWidth) - (_key == 'd' || _key == 'D') * 36 * (1.0f / windowWidth));
	viewPortTarget.y += ((_key == 's' || _key == 'S') * 36 * (1.0f / windowHeight) - (_key == 'w' || _key == 'W') * 36 * (1.0f / windowHeight));


	//Zooming
	if (_key == 'o' || _key == 'O') {
		zoomTarget /= 0.75;
	}
	else if (_key == 'p' || _key == 'P') {
		zoomTarget *= 0.75;
	}

	//Drawing mode activation is on key T
	if (_key == 't' || _key == 'T')
		setDrawingMode(true);

	//BONUS: Turn on/off Showing Grid and Snapping Grid 
	if (_key == 'g' || _key == 'G')
		glDrawer->switchGridOnOff();

	//ESC Key to exit
	if (_key == 27) {
		exit(0);
	}
}

void updateMousePositions(int _x, int _y) {
	pointMouseOnCanvas.x = ((_x - (viewPort.x*windowWidth / 2.0 + windowWidth / 2.0)) / zoom);
	pointMouseOnCanvas.y = ((_y - (viewPort.y*-windowHeight / 2.0 + windowHeight / 2.0)) / zoom);

	//Calculating the point SNAPPED to the grid 
	pointMouseOnCanvasSnappedToGrid.x = (glDrawer->getSnappedGridValueX(pointMouseOnCanvas.x));
	pointMouseOnCanvasSnappedToGrid.y = (glDrawer->getSnappedGridValueY(pointMouseOnCanvas.y));

	//Checking if cursor is within the boundries of Canvas
	isMouseInsideCanvas = glDrawer->isPointInsideOfCanvas(pointMouseOnCanvas);

	//Cursor manipulation
	if (isDrawingMode) {
		if (!isMouseInsideCanvas)
			glutSetCursor(GLUT_CURSOR_DESTROY);
		else
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	}
	else
		glutSetCursor(GLUT_CURSOR_INHERIT);

}

void funcMouseIdle(int _x, int _y)
{
	updateMousePositions(_x, _y);
}

void funcMouseDragging(int _x, int _y)
{
	updateMousePositions(_x, _y);

	//Pannig screen is disabled when drawing mode
	if (isDrawingMode)
		return;

	//Functions for panning the screen by mouse
	Point diff;
	diff.x = _x - pointMousePressed.x;
	diff.y = _y - pointMousePressed.y;

	pointMousePressed = { float(_x), float(_y) };
	viewPortTarget.x += diff.x * 2.0 * (1.0f / windowWidth);
	viewPortTarget.y -= diff.y * 2.0 * (1.0f / windowWidth);
}


static void funcMouse(int _btn, int _state, int _x, int _y)
{
	updateMousePositions(_x, _y);

	if (_state == GLUT_DOWN) {
		pointMousePressed = { float(_x), float(_y) };
		isPressingMouseButton = true;
	}
	else if (_state == GLUT_UP) {

		isPressingMouseButton = false;

		//ADDING A POINT TO POLYGON HERE
		if (isDrawingMode) {
			if (isMouseInsideCanvas) {
	
				//New point will be added into polygon
				//if (polygonDrawn->getSize() == 0)
				polygonDrawn->addPoint(pointMouseOnCanvasSnappedToGrid);

				pointLastAdded = pointMouseOnCanvasSnappedToGrid;

				if (polygonDrawn->getSize() > 1)
				if (dist(polygonDrawn->getFirstPoint(), pointMouseOnCanvasSnappedToGrid) < 8.0) {
					
					PolygonArray* newPolygon = new PolygonArray(polygonDrawn->getSize());

					//Need to copy data from vector to array
					for (int i = 0; i < polygonDrawn->getSize(); i++)
						newPolygon->addPoint(polygonDrawn->getPoint(i));

					polygonList.push_back(newPolygon);  //Pushing the draw polygon
					polygonDrawn->clearData();	  //Recreating new polygon for next drawing
					pointLastAdded = { -1, -1 };

					setDrawingMode(false);
				}
				
				
				//else
					//polygonDrawn->addPoint(pointMouseOnCanvasSnappedToGrid);
			}
		}
	}
}


static void drawCanvas()
{
	glDrawer->drawCanvasWithGrid();
}

static void drawPolygons()
{

	//if (polygonList.size() > 0)
		for (auto it = polygonList.begin(); it != polygonList.end(); ++it)
			glDrawer->drawPolygon(*it, COLOR_GREEN);

	if (polygonDrawn->getSize() > 1) {

		ColorType colorPolygonDrawn = COLOR_RED;

		if (dist(polygonDrawn->getFirstPoint(), pointMouseOnCanvasSnappedToGrid) < 5.0)
			colorPolygonDrawn = COLOR_GREEN;

		glDrawer->drawPolygon(polygonDrawn, colorPolygonDrawn);


		if (isDrawingMode && isMouseInsideCanvas && polygonDrawn->getSize() > 1 && isPressingMouseButton)
		{
			glDrawer->drawLine(pointLastAdded, pointMouseOnCanvasSnappedToGrid, COLOR_ORANGE, 2);
		}
	}
}

void funcDisplay() {

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(viewPort.x, viewPort.y, 0.0f);
	gluOrtho2D(-windowWidth / 2.0, windowWidth / 2.0, windowHeight / 2.0, -windowHeight / 2.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glScalef(zoom, zoom, zoom);

	drawCanvas();
	drawPolygons();

	glPopMatrix();
	glutSwapBuffers();

}

void funcTimer10ms(int _t) {

	zoom += (zoomTarget - zoom) / 10.0f;
	viewPort.x += ((viewPortTarget.x - viewPort.x) / 10.0f);
	viewPort.y += ((viewPortTarget.y - viewPort.y) / 10.0f);

	glutTimerFunc(10, funcTimer10ms, 0);
}


int main(int argc, char** argv) {

	funcInit();

	//Initializing GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowSize(1200, 800);
	glutCreateWindow("Relimetrics - OpenGL Assessment");
	glutInitWindowPosition(50, 50);

	glutTimerFunc(10, funcTimer10ms, 0);

	glutIdleFunc(funcIdle);
	glutMouseFunc(funcMouse);
	glutMotionFunc(funcMouseDragging);
	glutPassiveMotionFunc(funcMouseIdle);
	glutKeyboardFunc(funcKey);

	glutSpecialFunc(funcSpecialKey);

	glutReshapeFunc(funcReshape);
	glutDisplayFunc(funcDisplay);

	glutMainLoop();
	return 0;
}