/*
 * Relimetrics_OpenGL_Assesment - v0.2.3
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


GLint ww = 1200, hh = 800;

float zoom = 0.02;
float zoomTarget = 1.0f;

Point* viewPort;
Point* viewPortTarget;
Point* mouseOnScreen;
Point* mousePressed;
Point* mouseOnCanvas;

GLDrawer* glDrawer;

GLint vp[4];


int mainmode = MODE_NONE;
bool isDragging = false;

vector<Polygonic*> polygonList;
Polygonic* polygonDrawn;

static void setMainmode(Modes _mode)
{
	if (mainmode != _mode)
		mainmode = _mode;

	if (mainmode == Modes::MODE_DRAWING) {
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	}
	else if (mainmode == Modes::MODE_NONE) {
		glutSetCursor(GLUT_CURSOR_INHERIT);
	}
}

static void funcInit() {
	viewPort = new Point(0, 0);
	viewPortTarget = new Point(0, 0);

	mouseOnScreen = new Point(0, 0);
	mousePressed = new Point(0, 0);
	mouseOnCanvas = new Point(0, 0);

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

static void funcSpecialKey(int _key, int _x, int _y)
{
	switch (_key) {
	case GLUT_KEY_LEFT:
		viewPortTarget->setRelX(-36.0f * (1.0f / ww));
		break;
	case GLUT_KEY_RIGHT:
		viewPortTarget->setRelX(36.0f * (1.0f / ww));
		break;
	case GLUT_KEY_UP:
		viewPortTarget->setRelY(36.0f * (1.0f / hh));
		break;
	case GLUT_KEY_DOWN:
		viewPortTarget->setRelY(-36.0f * (1.0f / hh));
		break;
	}
}

void funcIdle()
{
	glutPostRedisplay();

}

static void funcKey(unsigned char _key, int x, int y)
{
	cout << _key;

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

void funcMouseDragging(int _x, int _y)
{
	mouseOnScreen->setXY(_x, _y);
	mouseOnCanvas->setX((_x - (viewPort->getX()*ww / 2.0 + ww / 2.0)) / zoom);
	mouseOnCanvas->setY((_y - (viewPort->getY()*-hh / 2.0 + hh / 2.0)) / zoom);

	if (isDragging == false)
		return;

	Point diff;
	diff.setXY(_x - mousePressed->getX(), _y - mousePressed->getY());

	mousePressed->setXY(_x, _y);
	viewPortTarget->setRelXY(diff.getX() * 2.0 * (1.0f / ww), diff.getY() * -2.0 * (1.0f / hh));
}

static void funcMouse(int _btn, int _state, int _x, int _y)
{
	mouseOnCanvas->setX((_x - (viewPort->getX()*ww / 2.0 + ww / 2.0)) / zoom);
	mouseOnCanvas->setY((_y - (viewPort->getY()*-hh / 2.0 + hh / 2.0)) / zoom);

	if (_state == GLUT_DOWN) {

		switch (_btn) {
		case GLUT_LEFT_BUTTON:
			cout << "left click at: (" << _x << ", " << _y << ")  << " << zoom << "\n";
			mousePressed->setXY(_x, _y);
			isDragging = true;
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
		isDragging = false;
	}
}


static void drawCanvas()
{
	glDrawer->drawCanvasWithGrid();
}

static void drawPolygons()
{


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

	glutKeyboardFunc(funcKey);
	glutSpecialFunc(funcSpecialKey);
	glutReshapeFunc(funcReshape);
	glutDisplayFunc(funcDisplay);
	glutMainLoop();
	return 0;
}