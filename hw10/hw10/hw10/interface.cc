/*************************************************************************
 FILE:   interface.cc
 Interface callback functions, window manipulation, display.

 Author: Dana Vrajitoru, IUSB
 Class:  C481 B581 Computer Graphics
 **************************************************************************/

#include "glheader.h"
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;
#include "geometry.h"

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLfloat trans[] = {0.0,0.0,1};
int option = 1;	//default draw function




	// Initialize one light source.
void lightInit()
{
	GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat lightDiffuse[]  = {1.0, 0.5, 0.5, 1.0};
	GLfloat lightSpecular[] = {0.1, 0.1, 0.1, 1.0};
	GLfloat lightPosition[] = {0.0, 5.0, -2.0, 1.0};

		// set up ambient, diffuse, and specular components for light 0

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glShadeModel(GL_SMOOTH); /*enable smooth shading */
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_LIGHT0);  /* enable light 0 */
	glEnable(GL_DEPTH_TEST); /* enable z buffer */
		//glEnable(GL_COLOR_MATERIAL);
		//glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

	glClearColor (0.1, 0.1, 0.1, 1.0);
	glColor3f (1, 0.0, 0.0);
}
	// Defining one particlar set of material properties that make the
	// objects following a call to this function blue and kind of shiny.
void materialWhite()
{	//RGB white
	GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat matDiffuse[]  = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat matShininess  = {2.5};

		// define material proerties for front face of all polygons
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
}
	// display function, calls the display list
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(0, 0, 3.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glTranslatef(trans[0], trans[1], 0);
	glScalef(trans[2], trans[2], trans[2]);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
		//change draw function by option value
	switch (option){
		case 1:
			cout<<"display form draw1() function\n"<<endl;
			glDisable(GL_LIGHTING);
			glDisable(GL_COLOR_MATERIAL);
			draw1();
			break;
		case 2:
			cout<<"display from draw2() function \n "<<endl;
			glDisable(GL_LIGHTING);
			glDisable(GL_COLOR_MATERIAL);
			draw2();
			break;
		case 3:
			cout<<"display from draw3() function\n"<<endl;
				//apply light & material
			glEnable(GL_LIGHTING);
			lightInit();
			materialWhite();
			draw3();
			break;
	}

	glFlush();
	glutSwapBuffers();
}


	// Idle callback, spin cube 2 degrees about selected axis
void spinObject()
{
	theta[axis] += 1.0;
	if( theta[axis] > 360.0 )
		theta[axis] -= 360.0;
	glutPostRedisplay();
}

	// callback for a mouse event, selects an axis about which to rotate
void mouse(int btn, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		glutIdleFunc(spinObject);
	else
		glutIdleFunc(NULL);

	switch (btn) {
		case GLUT_LEFT_BUTTON:
			axis = 0;
			break;
		case GLUT_MIDDLE_BUTTON:
			axis = 1;
			break;
		case GLUT_RIGHT_BUTTON:
			axis = 2;
	}
}

	// callback for the window size changing
void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, w/h, 1.0, 40.0);
	/*  if (w<=h)
	 glFrustum(-10.0, 10.0, -10.0 * (GLfloat) h/ (GLfloat) w,
	 10.0* (GLfloat) h / (GLfloat) w, -10.0, 20.0);
	 else
	 glFrustum(-10.0, 10.0, -10.0 * (GLfloat) w/ (GLfloat) h,
	 10.0* (GLfloat) w / (GLfloat) h, -10.0, 20.0);
	 */
	glMatrixMode(GL_MODELVIEW);
}

	// callback for key action
void key(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT:
			trans[0] -= 0.1;
			break;
		case GLUT_KEY_RIGHT:
			trans[0] += 0.1;
			break;
		case GLUT_KEY_UP:
			trans[1] += 0.1;
			break;
		case GLUT_KEY_DOWN:
			trans[1] -= 0.1;
			break;
		case GLUT_KEY_PAGE_UP:
			trans[2] += 0.1;
			break;
		case GLUT_KEY_PAGE_DOWN:
			trans[2] -= 0.1;

	}
	display();
}

	//to detect key pressed
void keyPressed (unsigned char key, int x, int y){
	if(key == '1'){
		option = 1;
	}else if(key == '2' ){
		option = 2;
	}else if(key == '3'){
		option = 3;
	}
	display();

}



	// various application parameters
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.25, 1.25, -1.25, 1.25);
	glMatrixMode(GL_MODELVIEW);
	glClearColor (1.0, 0.95, 0.9, 1.0);
	glColor3f(1.0,0.0,0.0);
	glutDisplayFunc(display);
	glutIdleFunc(NULL);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyPressed);
	glutReshapeFunc(myReshape);
	glutSpecialFunc(key);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
		//lightInit();
}
