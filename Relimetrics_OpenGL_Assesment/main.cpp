/*
 * Relimetrics_OpenGL_Assesment - v0.11
 * 
 * Created by Furkan Cetin (08/05/2021)
 * 
 */


#include <windows.h>  
#include <GL/glut.h> 

GLint ww = 1200, hh = 800;
GLint vp[4];

static void funcReshape(int _width, int _height)
{
	ww = _width;
	hh = _height;
	glViewport(0, 0, ww, hh);
	glGetIntegerv(GL_VIEWPORT, vp);
}

static void funcRender()
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-5.0f, -5.0f);
	glVertex2f(5.0f, -5.0f);
	glVertex2f(5.0f, 5.0f);
	glVertex2f(-5.0f, 5.0f);
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

	glutReshapeFunc(funcReshape);
	glutDisplayFunc(funcDisplay);								
	glutMainLoop();											
	return 0;
}