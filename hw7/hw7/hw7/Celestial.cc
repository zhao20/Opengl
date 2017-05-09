/*************************************************************************
  FILE:   Celestial.cc
          The Celestial class handling the creation, movement, and
          display of a base class representing a celestial body, plus
          all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

//#include <GL/glut.h>
#include "glheader.h"
#include "Celestial.h"
#include <iostream>
using namespace std;

// Constructor : initialize the default values and initialize the
// display list for the celestial body.
Celestial::Celestial(float rad)
    : radius(rad)
{
    dt = 0.3;
    thisId = glGenLists(1); // Gets the next available id for a
                            // display list.
    thisR = 1.0;            // white
    thisG = 1.0;
    thisB = 1.0;

    children = NULL;
    nrChildren = 0;
    
    // Create the display list.
    initDisplayList();
}

// set the color so that we can use it for several planets
void Celestial::setColor(float r, float g, float b)
{
    thisR = r;
    thisG = g;
    thisB = b;
}

// initialize the content of the display list, as a sphere by default
void Celestial::initDisplayList()
{
    glNewList(thisId, GL_COMPILE);
    glutSolidSphere(radius, 10, 10);
    glEndList();
}

// Performs one movement of the this in delta t.
void Celestial::move()
{
    for (int i=0; i<nrChildren; i++)
        children[i]->move();
}

// Calls the display list for the this after performing the
// appropriate transformations.
void Celestial::display()
{
    glPushMatrix();
    glColor3f(thisR, thisG, thisB);
    glCallList(thisId);
    for (int i=0; i<nrChildren; i++)
        children[i]->display();
    glPopMatrix();
}
