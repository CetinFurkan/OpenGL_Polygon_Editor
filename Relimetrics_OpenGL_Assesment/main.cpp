/*
 * Relimetrics_OpenGL_Assesment - v0.12
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
GLint vp[4];
float zoom = 1.0;

int mainmode = MODE_NONE;




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

static void funcKeyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 'o':
	case 'O':
		zoom *= 0.75;
		glutPostRedisplay();
		break;
	case 'p':
	case 'P':
		zoom /= 0.75;
		glutPostRedisplay();
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

static void funcMouse(int btn, int state, int x, int y)
{
	if (state == GLUT_DOWN) {

		switch (btn) {
		case GLUT_LEFT_BUTTON:
			std::cout << "left click at: (" << x << ", " << y << ")\n";
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
}


static void glColorRGB(GLfloat _r, GLfloat _g, GLfloat _b){
	glColor3f(_r/255.0f , _g / 255.0f, _b / 255.0f);
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
	glVertex2f(0.0f,  10000.0f);
	glVertex2f(0.0f, -10000.0f);
	glVertex2f(-10000.0f, 0.0f);
	glVertex2f( 10000.0f, 0.0f);
	glEnd();

}

void funcDisplay() {

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-ww/2.0f, ww/2.0f, -hh/2.0f, ww/2.0f);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glScalef(zoom, zoom, zoom);

	funcCoordinate();
	funcRender();

	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char** argv) {

	//Initializing GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Relimetrics - OpenGL Assessment"); 
	glutInitWindowSize(ww, hh);							
	glutInitWindowPosition(50, 50);

	glutMouseFunc(funcMouse);
	glutKeyboardFunc(funcKeyPressed);
	glutReshapeFunc(funcReshape);
	glutDisplayFunc(funcDisplay);								
	glutMainLoop();											
	return 0;
}