/*
 * Relimetrics_OpenGL_Assesment - v0.1
 * 
 * Created by Furkan Cetin (08/05/2021)
 * 
 */


#include <windows.h>  
#include <GL/glut.h> 


void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glFlush(); 
}

int main(int argc, char** argv) {

	//Initializing GLUT
	glutInit(&argc, argv);
	glutCreateWindow("Relimetrics - OpenGL Assessment"); 
	glutInitWindowSize(320, 320);							
	glutInitWindowPosition(50, 50);							
	glutDisplayFunc(display);								
	glutMainLoop();											
	return 0;
}