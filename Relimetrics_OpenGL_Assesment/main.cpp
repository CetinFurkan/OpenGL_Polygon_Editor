/*
 * Relimetrics_OpenGL_Assesment - v0.13
 *
 * Created by Furkan Cetin (08/05/2021)
 *
 */


#include <windows.h>  
#include <GL/glut.h> 
#include <iostream>

#define MODE_NONE    0;
#define MODE_DRAWING 1;

GLint ww = 1200, hh = 800;

float xx = 0.0f, yy = 0.0f;
float xxTarget = 0.0f, yyTarget = 0.0f;

GLint vp[4];
float zoom = 1.0;

int mousePressedX, mousePressedY;
int mouseX = 0, mouseY = 0;

int mainmode = MODE_NONE;
bool isDragging = false;



static void setMainmode(int _mode)
{
	if (mainmode != _mode)
		mainmode = _mode;
}

static void funcReshape(int _width, int _height)
{
	ww = _width;
	hh = _height;
	glViewport(0, 0, ww, hh);
	glGetIntegerv(GL_VIEWPORT, vp);
}

static void funcSpecialKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		xxTarget -= 36 * (1.0f / ww);;
		break;
	case GLUT_KEY_RIGHT:
		xxTarget += 36 * (1.0f / ww);;
		break;
	case GLUT_KEY_UP:
		yyTarget += 36 * (1.0f / hh);;
		break;
	case GLUT_KEY_DOWN:
		yyTarget -= 36 * (1.0f / hh);;
		break;
	}

	std::cout << "Movement: (" << xx << ", " << yy << ")\n";
}


static void funcKey(unsigned char key, int x, int y)
{
	switch (key) {
	case 'o':
	case 'O':
		zoom *= 0.75;
		break;
	case 'p':
	case 'P':
		zoom /= 0.75;

		break;
	case 'd':
	case 'D':
		mainmode = MODE_DRAWING;
		break;
	case 27:
		if (mainmode != 0)
			mainmode = 0;
		else
			exit(0);

		break;
	}
}

void mouseDragging(int x, int y)
{
	int diffx = x - mousePressedX;
	int diffy = y - mousePressedY;
	mousePressedX = x;
	mousePressedY = y;

	xxTarget += diffx * (1.0f / ww);
	yyTarget -= diffy * (1.0f / hh);
}

static void funcMouse(int btn, int state, int x, int y)
{
	if (state == GLUT_DOWN) {

		switch (btn) {
		case GLUT_LEFT_BUTTON:
			std::cout << "left click at: (" << x << ", " << y << ")\n";
			mousePressedX = x;
			mousePressedY = y;
			isDragging = true;
			break;
		case GLUT_RIGHT_BUTTON:
			std::cout << "right click at: (" << x << ", " << y << ")\n";
			break;
		case GLUT_MIDDLE_BUTTON:
			std::cout << "middle click at: (" << x << ", " << y << ")\n";
			break;
		default:
			break;
		}
	}
	else if (state == GLUT_UP && btn == GLUT_LEFT_BUTTON) {
		isDragging = false;
	}
}


static void glColorRGB(GLfloat _r, GLfloat _g, GLfloat _b) {
	glColor3f(_r / 255.0f, _g / 255.0f, _b / 255.0f);
}

static void funcRender()
{
	glBegin(GL_QUADS);
	glColorRGB(255, 0, 0);
	glVertex2f(-50.0f, -50.0f);
	glVertex2f(50.0f, -50.0f);
	glVertex2f(50.0f, 50.0f);
	glVertex2f(-50.0f, 50.0f);
	glEnd();
}

static void funcCoordinate()
{
	glBegin(GL_LINES);
	glColorRGB(255, 255, 255);
	glVertex2f(0.0f, 10000.0f);
	glVertex2f(0.0f, -10000.0f);
	glVertex2f(-10000.0f, 0.0f);
	glVertex2f(10000.0f, 0.0f);
	glEnd();

}

void funcDisplay() {


	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(xx, yy, 0.0f);
	gluOrtho2D(ww / 2.0f, -ww / 2.0f, hh / 2.0f, -hh / 2.0f);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glScalef(zoom, zoom, zoom);

	funcCoordinate();
	funcRender();

	glPopMatrix();
	glutSwapBuffers();

}

void funcTimer20ms(int _t) {

	if (abs(xxTarget - xx) < 1) 
	{
		xx = xxTarget;
		yy = yyTarget;
	}
	else 
	{
		xx += (xxTarget - xx) / 330.0f;
		yy += (yyTarget - yy) / 330.0f;
	}

	glutPostRedisplay();
	glutTimerFunc(20, funcTimer20ms, 0);
}

int main(int argc, char** argv) {

	//Initializing GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Relimetrics - OpenGL Assessment");
	glutInitWindowSize(ww, hh);

	glutInitWindowPosition(50, 50);

	glViewport(0, 0, ww, hh);

	glutTimerFunc(20, funcTimer20ms, 0);

	glutMouseFunc(funcMouse);
	glutMotionFunc(mouseDragging);

	glutKeyboardFunc(funcKey);
	glutSpecialFunc(funcSpecialKey);
	glutReshapeFunc(funcReshape);
	glutDisplayFunc(funcDisplay);
	glutMainLoop();
	return 0;
}