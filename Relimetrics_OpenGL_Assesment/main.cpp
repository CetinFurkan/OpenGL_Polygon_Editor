/*
 * Relimetrics_OpenGL_Assesment - v0.3.0
 *
 * Created by Furkan Cetin (08/05/2021)
 *
 */


#include <windows.h>  
#include "Common.h"

#include "GLDrawer.h"


enum Modes
{
	MODE_NONE,
	MODE_DRAWING,
	MODE_EDITING,
	MODE_POPUP,
};

enum Directions
{
	DIR_RIGHT,
	DIR_UP,
	DIR_LEFT,
	DIR_DOWN,
};

GLint ww = 1200, hh = 800;

float zoom = 0.02;
float zoomTarget = 1.0f;

Point* viewPort;
Point* viewPortTarget;
Point* pointMouseOnScreen;
Point* pointMousePressed;
Point* pointMouseOnCanvas;
Point* pointMouseOnCanvasSnappedToGrid;
Point* pointLastAdded;

GLDrawer* glDrawer;

GLint vp[4];


int mainmode = MODE_NONE;
bool isPressingMouseButton = false;
bool isMouseInsideCanvas = false;

vector<Polygonic*> polygonList;
Polygonic* polygonDrawn;

static void setMainmode(Modes _mode)
{
	//These details are required for actions during the transitions between modes
	if (mainmode == Modes::MODE_NONE)
	{
		if (mainmode == Modes::MODE_DRAWING) {
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		}
		else if (mainmode == Modes::MODE_EDITING) {
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
	}
	else if (mainmode == Modes::MODE_DRAWING)
	{
		if (mainmode == Modes::MODE_NONE) {
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		else if (mainmode == Modes::MODE_EDITING) {
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
	}
	else if (mainmode == Modes::MODE_EDITING)
	{
		if (mainmode == Modes::MODE_NONE) {
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		else if (mainmode == Modes::MODE_DRAWING) {
			glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		}
	}

	if (mainmode != _mode)
		mainmode = _mode;
}

static void funcInit() {
	viewPort = new Point(0, 0);
	viewPortTarget = new Point(0, 0);

	pointMouseOnScreen = new Point(0, 0);
	pointMousePressed = new Point(0, 0);
	pointMouseOnCanvas = new Point(0, 0);
	pointMouseOnCanvasSnappedToGrid = new Point(0, 0);

	pointLastAdded = new Point(-1, -1);

	glDrawer = new GLDrawer();
	glDrawer->setCanvasPorperties(1200, 800, 20, GRID_TYPE_SQUARE_POINTS);

	polygonDrawn = new Polygonic();
}

static void funcReshape(int _width, int _height)
{
	ww = _width;
	hh = _height;
	glViewport(0, 0, ww, hh);
	glGetIntegerv(GL_VIEWPORT, vp);
}

void panScreen(Directions _dir, float _amount) {
	if (_dir == DIR_LEFT) {
		viewPortTarget->setRelX(_amount * (1.0f / ww));
	}
	else 	if (_dir == DIR_RIGHT) {
		viewPortTarget->setRelX(-_amount * (1.0f / ww));
	}

	if (_dir == DIR_UP) {
		viewPortTarget->setRelY(-_amount * (1.0f / hh));
	}
	else 	if (_dir == DIR_DOWN) {
		viewPortTarget->setRelY(_amount * (1.0f / hh));
	}
}

static void funcSpecialKey(int _key, int _x, int _y)
{
	if (_key == GLUT_KEY_LEFT)
		panScreen(DIR_LEFT, 40);
	else if (_key == GLUT_KEY_RIGHT)
		panScreen(DIR_RIGHT, 40);


	if (_key == GLUT_KEY_UP)
		panScreen(DIR_UP, 40);
	else if (_key == GLUT_KEY_DOWN)
		panScreen(DIR_DOWN, 40);
}

void funcIdle()
{
	glutPostRedisplay();
}


static void funcKey(unsigned char _key, int x, int y)
{
	viewPortTarget->setRelX((_key == 'd' || _key == 'D') * 36 * (1.0f / ww) - (_key == 'a' || _key == 'A') * 36 * (1.0f / ww));
	viewPortTarget->setRelY((_key == 'w' || _key == 'W') * 36 * (1.0f / hh) - (_key == 's' || _key == 'S') * 36 * (1.0f / hh));

	if (_key == 'o' || _key == 'O') {
		zoomTarget *= 0.75;
		cout << zoomTarget;
	}
	else if (_key == 'p' || _key == 'P') {
		zoomTarget /= 0.75;
		cout << zoomTarget;
	}

	if (_key == 't' || _key == 'T')
		setMainmode(MODE_DRAWING);

	if (_key == 27) {
		if (mainmode != 0)
			setMainmode(MODE_NONE);
		else
			exit(0);
	}
}

void updateMousePositions(int _x, int _y) {
	pointMouseOnScreen->setXY(_x, _y);
	pointMouseOnCanvas->setX((_x - (viewPort->getX()*ww / 2.0 + ww / 2.0)) / zoom);
	pointMouseOnCanvas->setY((_y - (viewPort->getY()*-hh / 2.0 + hh / 2.0)) / zoom);

	//Calculating the point SNAPPED to the grid
	pointMouseOnCanvasSnappedToGrid->setX(glDrawer->getSnappedGridValueX(pointMouseOnCanvas->getX()));
	pointMouseOnCanvasSnappedToGrid->setY(glDrawer->getSnappedGridValueY(pointMouseOnCanvas->getY()));

	isMouseInsideCanvas = glDrawer->isPointInsideOfCanvas(pointMouseOnCanvas);

	if (mainmode == MODE_DRAWING) {
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

	if (mainmode == MODE_DRAWING)
		return;

	//Functions for panning the screen by mouse
	Point diff;
	diff.setXY(_x - pointMousePressed->getX(), _y - pointMousePressed->getY());

	pointMousePressed->setXY(_x, _y);
	viewPortTarget->setRelXY(diff.getX() * 2.0 * (1.0f / ww), diff.getY() * -2.0 * (1.0f / hh));
}

static void funcMouse(int _btn, int _state, int _x, int _y)
{
	updateMousePositions(_x, _y);

	if (_state == GLUT_DOWN) {
		isPressingMouseButton = true;
		switch (_btn) {
		case GLUT_LEFT_BUTTON:
			cout << "left click at: (" << _x << ", " << _y << ")  << " << zoom << "\n";
			pointMousePressed->setXY(_x, _y);
			break;
		case GLUT_RIGHT_BUTTON:
			cout << "right click at: (" << _x << ", " << _y << ")\n";
			break;
		case GLUT_MIDDLE_BUTTON:
			cout << "middle click at: (" << _x << ", " << _y << ")\n";
			break;
		default:
			break;
		}
	}
	else if (_state == GLUT_UP && _btn == GLUT_LEFT_BUTTON) {
		isPressingMouseButton = false;

		if (mainmode == MODE_DRAWING) {
			if (glDrawer->isPointInsideOfCanvas(pointMouseOnCanvas)) {

				Point* pointNewToAdd = new Point(pointMouseOnCanvasSnappedToGrid);

				pointLastAdded->setXYfromPoint(pointNewToAdd);

				polygonDrawn->addPoint(pointNewToAdd);
				if (polygonDrawn->checkIfClosed()) {
					setMainmode(MODE_NONE);
					polygonList.push_back(polygonDrawn);
					polygonDrawn = new Polygonic();
					pointLastAdded->setXY(-1, -1);
				}
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
	for (auto it = polygonList.begin(); it != polygonList.end(); ++it)
		glDrawer->drawPolygon(*it, COLOR_BLUE, 2);

	ColorType colorPolygonDrawn = COLOR_RED;
	if (polygonDrawn->checkPointIsCloseToFirstPoint(pointMouseOnCanvasSnappedToGrid))
		colorPolygonDrawn = COLOR_GREEN;

	glDrawer->drawPolygon(polygonDrawn, colorPolygonDrawn, 2);

	if (mainmode == MODE_DRAWING && isMouseInsideCanvas && pointLastAdded->getX() > -1 && isPressingMouseButton)
	{
		glDrawer->drawLine(pointLastAdded, pointMouseOnCanvasSnappedToGrid, COLOR_ORANGE, 2);
	}

}

void funcDisplay() {

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(viewPort->getX(), viewPort->getY(), 0.0f);
	gluOrtho2D(-ww / 2.0, ww / 2.0, hh / 2.0, -hh / 2.0);
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
	viewPort->setRelX((viewPortTarget->getX() - viewPort->getX()) / 10.0f);
	viewPort->setRelY((viewPortTarget->getY() - viewPort->getY()) / 10.0f);

	glutTimerFunc(10, funcTimer10ms, 0);
}

void funcTimer100ms(int _t) {

	glutTimerFunc(100, funcTimer100ms, 0);
}

void funcTimer1000ms(int _t) {

	glutTimerFunc(1000, funcTimer1000ms, 0);
}


int main(int argc, char** argv) {

	funcInit();

	//Initializing GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowSize(1200, 800);
	glutCreateWindow("Relimetrics - OpenGL Assessment");

	glutInitWindowPosition(50, 50);

	glutIdleFunc(funcIdle);

	glutTimerFunc(20, funcTimer10ms, 0);
	glutTimerFunc(100, funcTimer100ms, 0);
	glutTimerFunc(1000, funcTimer1000ms, 0);

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