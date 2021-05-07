/*
 * Relimetrics_OpenGL_Assesment - v0.12
 * 
 * Created by Furkan Cetin (08/05/2021)
 * 
 */


#include <windows.h>  
#include <GL/glut.h> 

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
		exit(0);
	}
}

static void funcRender()
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-50.0f, -50.0f);
	glVertex2f(50.0f, -50.0f);
	glVertex2f(50.0f, 50.0f);
	glVertex2f(-50.0f, 50.0f);
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

	glutKeyboardFunc(funcKeyPressed);
	glutReshapeFunc(funcReshape);
	glutDisplayFunc(funcDisplay);								
	glutMainLoop();											
	return 0;
}