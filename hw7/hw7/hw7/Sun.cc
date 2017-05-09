/*************************************************************************
  FILE:   Sun.cc
          The Sun class handling the creation, movement, and display of 
          the class, plus all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

//#include <GL/glut.h>
#include "glheader.h"
#include "Sun.h"
#include "Earth.h"
#include "Mars.h"
#include "Saturn.h"
#include "Jupiter.h"
#include <iostream>
using namespace std;

// Constructor : initialize the default values and initialize the
// display list for the Sun.
Sun::Sun() 
    : Celestial(0.5)
{
    // redefine the color
    thisR = 1.0;
    thisG = 1.0;
    thisB = 0.2;

    // add one child 
    nrChildren = 6;
    children = new CelestialPtr[nrChildren];
    children[0] = new Earth();
	children[1] = new Mars();
	children[2] = new Planet(0.1, 20, 3, 0);//mercury
	children[2]->setColor(0.686,0.365,0.0);
	children[3] = new Planet(0.22, 8.2, 4, 0);//venus
	children[3]->setColor(1.0, 0.8235, 0.302);
	children[4] = new Saturn();	//Saturn
	children[5] = new Jupiter(); //Jupiter
    initDisplayList();
}

// initialize the content of the display list, as a sphere for the sun
// and a reference disc so that we can see the what's happening
void Sun::initDisplayList()
{
    GLUquadricObj *obj;
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_LINE);
    gluQuadricNormals(obj,  GLU_FLAT);

    // Create the display list.
    glNewList(thisId, GL_COMPILE);
    glColor3f(thisR, thisG, thisB);
    // The sun itself.
    glutSolidSphere(radius, 10, 10);

    // A reference disk so we can see what's going on.
    glPushMatrix();
    glColor3f(0.4, 0.3, 0.6);
    glRotatef(90, 1.0, 0, 0);
    gluDisk(obj, 0, 40.0, 20, 20);
    glPopMatrix();
    glEndList();
}
