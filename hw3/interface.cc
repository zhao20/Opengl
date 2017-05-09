/********************************************************************
 File:         interface.cc
 Author:       Dana Vrajitoru
 Project:      A fractal program
 Last updated: January 30, 2017.

 Interface functions for the fractal program.

 ********************************************************************/

#include "glheader.h"
#include "interface.h"
#include "sierpinski.h"
#include <cstdlib>
#include <stdio.h>

int width = 500, height = 500;

float squareWidth = 1.75;

float tx =0.0, ty = 0.0;
float factor = 1;

/* initial triangle */

Point2 v[]={{-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15}};

int n;

	// Create a window and set up the GUI functions
void createWindowGUI()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(width, height);
	glutCreateWindow("2D Gasket");
	glutReshapeFunc(myResize);
	glutDisplayFunc(display);
		//glutIdleFunc(display);
	glutKeyboardFunc(key);
	glutSpecialFunc(spkey);
		//glutMouseFunc(mouse);
}

	// Application parameters
void myinit()
{
	n = 5;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.25, 1.25, -1.25, 1.25);
	glMatrixMode(GL_MODELVIEW);
	glClearColor (0, 0, 0, 1.0);//black
	glColor3f(1.0,0.0,0.0);     // red
								//glLineWidth(2);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
}

	// To be called whenever the window is resized.
void myResize(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.25, 1.25, -1.25, 1.25);
	glMatrixMode(GL_MODELVIEW);
}

	// Callback function for the display
void display(void)
{

	glLoadIdentity();	//set coordinate
	glTranslatef(tx,ty,0.0f);	//moving coordiante original point to new position
	glScalef(factor, factor, 1);	// zoom in and zoom out
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor (0.0, 0.0, 0.0, 1.0);//black
	glColor3f(1.0,0.0,0.0);     // red
								//divide_triangle(v[0], v[1], v[2], 0);
								//triangle(v[0], v[1], v[2]);
	carpet(v[0], squareWidth, n);
		//square(v[0], 1.75);
	glFlush();
}

	// Callback function for an Ascii key being pressed
void key(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q':
		case 'Q':
			exit(0);
				//reset to original value
		case 'r':
		case 'R':
			squareWidth = 1.75;
			n=5;
			tx = 0;
			ty = 0;
			factor = 1;
			display();
			glutPostRedisplay();
			break;

		case '1': 		//level of squares
			n = 2;
			glutPostRedisplay();
			break;
		case '2':		//3 level detail
			n = 3;
			glutPostRedisplay();
			break;
		case '3':		//4 levels
			n = 4;
			glutPostRedisplay();
			break;
		case '4':		//5 levels
			n = 5;
			glutPostRedisplay();
			break;
		case '5':		//6 levels
			n = 6;
			glutPostRedisplay();
			break;
	}
}

	// Callback function for a special key being pressed
void spkey(int key, int x, int y)
{
	switch (key) {
				//move to left
		case GLUT_KEY_LEFT:
			tx-=0.1;
			break;
				//move to right
		case GLUT_KEY_RIGHT:
			tx += 0.1;
			break;
				//move to up
		case GLUT_KEY_UP:
			ty += 0.1;
			break;
				//move to down
		case GLUT_KEY_DOWN:
			ty -= 0.1;
			break;
				//zoom in
		case GLUT_KEY_PAGE_UP:
			factor += 0.1;
			break;
				//zoom out
		case GLUT_KEY_PAGE_DOWN:
			if(factor >0)
				factor -= 0.1;
			break;
	}
	display();
	glutPostRedisplay();
}
