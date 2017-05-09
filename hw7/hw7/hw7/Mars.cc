/*************************************************************************
  FILE:   Mars.cc
          The Mars class handling the creation, movement, and display of 
          the class, plus all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

//#include <GL/glut.h>
#include "glheader.h"
#include "Mars.h"

// Constructor : initialize the default values and initialize the
// display list for the Earth.
Mars::Mars()
    : Planet(0.15, 4.5, 6, 0)
{
    // redefine the color
    thisR = 1.0;
    thisG = 0.251;
    thisB = 0.0;

    // add the moon
    nrChildren = 2;
    children = new CelestialPtr[nrChildren]; 
    children[0] = new Planet(0.02, -4, 0.4, 60);
	children[1] = new Planet(0.03, -7, 0.2, 0);
}
