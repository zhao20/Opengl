/*************************************************************************
  FILE:   Earth.cc
          The Earth class handling the creation, movement, and display of 
          the class, plus all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

//#include <GL/glut.h>
#include "glheader.h"
#include "Earth.h"

// Constructor : initialize the default values and initialize the
// display list for the Earth.
Earth::Earth()
    : Planet(0.2, 5, 5, 0)
{
    // redefine the color
    thisR = 0.3;
    thisG = 0.3;
    thisB = 1.0;

    // add the moon
    nrChildren = 1;
    children = new CelestialPtr[nrChildren]; // the moon
    children[0] = new Planet(0.08, 15, 0.6, 60);
}
