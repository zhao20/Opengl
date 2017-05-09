				/********************************************************************
 File:         interface.cc
 Author:       Dana Vrajitoru
 Project:      Optical illusion
 Last updated: January 23, 2017.

 Interface functions for the program.

 ********************************************************************/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "glheader.h"
#include "interface.h"
#include "illusion.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int winWidth = 600, winHeight = 400;
int backgroundSequence = 0;		//index for switching colors
int increasementUnit = 5; 		//increasement of gap each time
int gap = 5;		//base base between lines


	// some colors to play with
float black[3] = {0.0, 0.0, 0.0};
float white[3] = {1.0, 1.0, 1.0};
float red[3]   = {1.0, 0.0, 0.0};
float green[3] = {0.0, 1.0, 0.0};
float blue[3]  = {0.0, 0.0, 1.0};
float purple[3] = {0.8, 0.0, 1.0};
float yellow[3] = {0.6, 1.0, 0.8};
float orange[3] = {0.3, 1.0,0.5};
float pink[3] = {0.0, 1.0, 0.88};
	// Create a window and set up the GUI functions
void createWindowGUI()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Lens Illusion");
	glutDisplayFunc(display);
	glutReshapeFunc(myResize);
		//glutIdleFunc(display);
	glutKeyboardFunc(key);
	glutSpecialFunc(spkey);
		//glutMouseFunc(mouse);
}

	// Defining some of the application parameters
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winWidth, 0, winHeight);
	glMatrixMode(GL_MODELVIEW);
	glClearColor (purple[0], purple[1], purple[2], 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2);
	display();
}

	// To be called whenever the window is resized.
void myResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winWidth, 0, winHeight);
	glMatrixMode(GL_MODELVIEW);
}

	// Callback function for redrawing the window
void display(void)
{
		// set the background in the color we want
	glClear(GL_COLOR_BUFFER_BIT);
		//to switch color by numbers
	switch(backgroundSequence){
		case 0:
			glClearColor (purple[0], purple[1], purple[2], 1.0);
			break;
		case 1:
			glClearColor (red[0], red[1], red[2], 1.0);
			break;
		case 2:
			glClearColor (green[0], green[1], green[2], 1.0);
			break;
		case 3:
			glClearColor (blue[0], blue[1], blue[2], 1.0);
			break;

		case 4:
			glClearColor (yellow[0], yellow[1], yellow[2], 1.0);
			break;
		case 5:
			glClearColor (orange[0], orange[1], orange[2], 1.0);
			break;
		case 6:
			glClearColor (pink[0], pink[1], pink[2], 1.0);
			break;
		case 7:
			glClearColor (black[0], black[1], black[2], 1.0);
			break;
	}


		// draw the illution
	lensIllusion(gap, white, winWidth, winHeight);
		// send the content of the view buffer to the window
	glFlush();

}

	// Callback function for an Ascii key being pressed
void key(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q':
		case 'Q':
			exit(0);
		case 'r':
		case 'R':
				//reset height and width to original size
			winHeight = 400;
			winWidth = 600;
			gap = 5;	//reset gap to original
			backgroundSequence = 0;		//reset background color
			myResize(winWidth, winHeight);	//resize the illusion
			glutReshapeWindow(winWidth,winHeight);	//reset window size
			break;
		case ' ':
				//to switch background between 0 - 7
			backgroundSequence = (backgroundSequence +1)%8;
			break;

	}
		//reactive the background color and lenillusion
	display();
	glutPostRedisplay();


}

	// Callback function for a special key being pressed
void spkey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT:
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
				//increase width
			winWidth += increasementUnit;
				//increase height
			winHeight += increasementUnit;
				//resize the illusion
			myResize(winWidth, winHeight);
			break;
		case GLUT_KEY_DOWN:
				//check width or height cannot less than 0
			if(winWidth>increasementUnit && winHeight>increasementUnit){
				winWidth-=increasementUnit;
				winHeight -= increasementUnit;
			}
				//resize the diplay
			myResize(winWidth, winHeight);
			break;
		case GLUT_KEY_PAGE_UP:
				//incrase gap by page up key
			gap ++;
			break;
		case GLUT_KEY_PAGE_DOWN:
				//decrease gap by page down key
			if(gap >1) gap--;
				//glutPostRedisplay();
			break;

	}
	display();		//apply the changes
	glutPostRedisplay();
}

