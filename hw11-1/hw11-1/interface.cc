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
#include "Maze.h"
#include "interface.h"
#include "bitmap.h"
#include "Player.h"

int width = 800, height = 600;

static GLfloat theta[] = {308.0, 0.0, 0.0};
static GLint axis = 2;
static GLfloat trans[] = {3.4, 1.5, 0.3};

char *brick_texture, *floor_texture, *food_texture;
int widtht, heightt, widthf, heightf;

Maze board;
Player actor;

	// display function, calls the display list
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(6, 5, -3.5, 5.0, 1.0, 10.0, 0.0, 1.0, 0.5);

	light0();
		//materialBlue();

	glTranslatef(trans[0], trans[1], 0);
	glScalef(trans[2], trans[2], trans[2]);
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	board.display();
	actor.display();
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
	gluPerspective(60.0, w/h, 1.0, 40.0);
	width = w;
	height = h;
	/*  if (w<=h)
	 glFrustum(-10.0, 10.0, -10.0 * (GLfloat) h/ (GLfloat) w,
	 10.0* (GLfloat) h / (GLfloat) w, -10.0, 20.0);
	 else
	 glFrustum(-10.0, 10.0, -10.0 * (GLfloat) w/ (GLfloat) h,
	 10.0* (GLfloat) w / (GLfloat) h, -10.0, 20.0);
	 */
	glMatrixMode(GL_MODELVIEW);
}

	// callback for special key action
void spkey(int key, int x, int y)
{
	static float speed = 0.2;
	switch (key) {
		case GLUT_KEY_LEFT:
				//trans[0] -= 0.1;
			actor.moveHorizontal(speed);
			break;
		case GLUT_KEY_RIGHT:
				//trans[0] += 0.1;
			actor.moveHorizontal(-speed);
			break;
		case GLUT_KEY_UP:
				//trans[1] += 0.1;
			actor.moveVertical(speed);
			break;
		case GLUT_KEY_DOWN:
				//trans[1] -= 0.1;
			actor.moveVertical(-speed);
			break;
		case GLUT_KEY_PAGE_UP:
				//trans[2] += 0.1;
			break;
		case GLUT_KEY_PAGE_DOWN:
				//trans[2] -= 0.1;
			break;
	}
	display();
}


	// callback for key action
void key(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'p':
		case'P':
			cout << "Translation: "<< trans[0] << ' ' << trans[1] << ' '
			<< trans[2] << endl;
			cout << "Rotation: "<< theta[0] << ' ' << theta[1] << ' '
			<< theta[2] << endl;
			break;
	}
	display();
}

	// set up ambient, diffuse, and specular components for light 0
void light0()
{

	GLfloat lightAmbient[]={0.5, 0.5, 0.5, 1.0};
	GLfloat lightDiffuse[]={0.5, 0.5, 0.5, 1.0};
	GLfloat lightSpecular[]={1.0, 1.0, 1.0, 1.0};
	GLfloat lightPosition[]={0.0, 0.0, 0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

	// Defining one particlar set of material properties that make the
	// objects following a call to this function blue and kind of shiny.
void materialBlue()
{
	GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat matDiffuse[]  = {0.0, 0.0, 0.5, 1.0};
	GLfloat matAmbient[] = {0.5, 0.5, 1.0, 1.0};
	GLfloat matShininess  = {2.5};

		// define material proerties for front face of all polygons

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
}

	// create a texture from a pixel data buffer
void makeTexture(char *buffer, int width, int height)
{
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
				 GL_RGB, GL_UNSIGNED_BYTE, buffer);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
}

	// create the scene objects
void createObjects()
{
	board.init();
	board.loadTextures();
	board.textureOn = true;
	actor.draw();
	actor.world = &board;
		//actor.loadTextures();
	actor.teleport(7, 1); // center bottom of the maze
}

	// various application parameters
void myinit()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize(width, height);
	glutCreateWindow("Maze");
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, width/height, 1.0, 40.0);
	glMatrixMode(GL_MODELVIEW);

	glClearColor (1.0, 0.95, 0.9, 1.0);
	glColor3f(1.0,0.0,0.0);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);
	glutIdleFunc(NULL);
		//glutMouseFunc(mouse);
	glutReshapeFunc(myReshape);
	glutSpecialFunc(spkey);

	glShadeModel(GL_SMOOTH); // enable smooth shading
	glEnable(GL_LIGHTING);   // enable lighting
	glEnable(GL_LIGHT0);     // enable light 0
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
}
