/*
 * Relimetrics_OpenGL_Assesment - v0.2.1
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

Point* viewPort;
Point* viewPortTarget;
Point* mouseNow;
Point* mousePressed;

GLDrawer* glDrawer;

GLint vp[4];
float zoom = 1.0;


int mainmode = MODE_NONE;
bool isDragging = false;

vector<Polygonic> polygonList;


static void setMainmode(int _mode)
{
	if (mainmode != _mode)
		mainmode = _mode;
}

static void funcInit() {
	viewPort = new Point(0, 0);
	viewPortTarget = new Point(0, 0);

	mouseNow = new Point(0, 0);
	mousePressed = new Point(0, 0);

	glDrawer = new GLDrawer();
	glDrawer->setCanvasPorperties(800,600,20,GRID_TYPE_SQUARE_POINTS);
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
		viewPortTarget->setRelXf(-36.0f * (1.0f / ww));
		break;
	case GLUT_KEY_RIGHT:
		viewPortTarget->setRelXf(36.0f * (1.0f / ww));
		break;
	case GLUT_KEY_UP:
		viewPortTarget->setRelYf(36.0f * (1.0f / hh));
		break;
	case GLUT_KEY_DOWN:
		viewPortTarget->setRelYf(-36.0f * (1.0f / hh));
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

	viewPortTarget->setRelXf((_key == 'd' || _key == 'D') * 36 * (1.0f / ww) - (_key == 'a' || _key == 'A') * 36 * (1.0f / ww));
	viewPortTarget->setRelYf((_key == 'w' || _key == 'W') * 36 * (1.0f / hh) - (_key == 's' || _key == 'S') * 36 * (1.0f / hh));

	if (_key == 'o' || _key == 'O') {
		zoom *= 0.75;
		cout << zoom;
	}
	else if (_key == 'p' || _key == 'P') {
		zoom /= 0.75;
		cout << zoom;
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

void mouseDragging(int _x, int _y)
{
	mouseNow->setXY(_x, _y);

	if (isDragging == false)
		return;

	Point diff;
	diff.setXY(_x - mousePressed->getX(), _y - mousePressed->getY());
	//cout << diff.getX() << "|" << diff.getY() << endl;

	mousePressed->setXY(_x, _y);
	viewPortTarget->setRelXYf(diff.getXf() * 2.0 * (1.0f / ww)  , diff.getYf() * -2.0 * (1.0f / hh));
}

static void funcMouse(int _btn, int _state, int _x, int _y)
{
	if (_state == GLUT_DOWN) {

		switch (_btn) {
		case GLUT_LEFT_BUTTON:
			cout << "left click at: (" << _x << ", " << _y << ")\n";
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
	/*
	glBegin(GL_LINE_LOOP);
	glColorRGB(255,0,0);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, hh);
	glVertex2f(  ww, hh);
	glVertex2f(  ww, 0.0f);
	glEnd();*/
	
}

static void drawGrid()
{

	
}

void funcDisplay() {

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(viewPort->getXf(), viewPort->getYf(), 0.0f);
	gluOrtho2D(ww / 2.0f, -ww / 2.0f, hh / 2.0f, -hh / 2.0f);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glScalef(zoom, zoom, zoom);

	drawGrid();
	drawCanvas();

	glPopMatrix();
	glutSwapBuffers();

}

void funcTimer10ms(int _t) {

	if (false && dist(viewPortTarget, viewPort) < 1)
	{
		viewPort->setXYfromPoint(viewPortTarget);  //Makes equal to target point, so moving stops
	}
	else //there needs to be moving to the target point
	{
		
		viewPort->setRelXf((viewPortTarget->getXf() - viewPort->getXf()) / 15.0f);
		viewPort->setRelYf((viewPortTarget->getYf() - viewPort->getYf()) / 15.0f);
	}

	glutTimerFunc(10, funcTimer10ms, 0); //keeping the loop going
}

int main(int argc, char** argv) {

	funcInit();

	//Initializing GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Relimetrics - OpenGL Assessment");
	glutInitWindowSize(ww, hh);

	glutInitWindowPosition(50, 50);

	glutIdleFunc(funcIdle);

	glutTimerFunc(20, funcTimer10ms, 0);

	glutMouseFunc(funcMouse);
	glutMotionFunc(mouseDragging);

	glutKeyboardFunc(funcKey);
	glutSpecialFunc(funcSpecialKey);
	glutReshapeFunc(funcReshape);
	glutDisplayFunc(funcDisplay);
	glutMainLoop();
	return 0;
}