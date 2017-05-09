/*************************************************************************
  FILE:   Saturn.cc
          The Earth class handling the creation, movement, and display of 
          the class, plus all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

//#include <GL/glut.h>
#include "glheader.h"
#include "Saturn.h"

// Constructor : initialize the default values and initialize the
// display list for the Earth.
Saturn::Saturn()
    : Planet(0.4, 2, 11, 120)
{
    // redefine the color
    thisR = 0.886;
    thisG = 0.525;
    thisB = 0.0078;
	initDisplayList();

}

	// and a reference disc so that we can see the what's happening
void Saturn::initDisplayList()
{
	GLUquadricObj *obj;
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluQuadricNormals(obj,  GLU_FLAT);

		// Create the display list.
	glNewList(thisId, GL_COMPILE);
	glColor3f(thisR, thisG, thisB);
		// The sun itself.
	glutSolidSphere(radius, 10, 10);

		// A reference disk so we can see what's going on.
	glPushMatrix();
	glColor3f(1.0, 0.95, 0.5);
	glRotatef(60, 1.0, 0, 0);
	gluDisk( obj, 0.5, 0.75, 100, 20);
	glPopMatrix();
	glEndList();
}
