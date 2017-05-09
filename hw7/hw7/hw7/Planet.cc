/*************************************************************************
  FILE:   Planet.cc
          The Planet class handling the creation, movement, and display of 
          the class, plus all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

//#include <GL/glut.h>
#include "glheader.h"
#include "Planet.h"
#include <iostream>
using namespace std;

// Constructor : initialize the default values and initialize the
// display list for the planet.
Planet::Planet(float rad, float aSpeed, float orb, float startAngle)
    : Celestial(rad)
{
    // specific planet attributes
    speed = aSpeed; // angular speed
    orbit = orb;
    angle = startAngle;
}

// Performs one movement of the planet in delta t.
void Planet::move()
{
    float deltaAngle = speed * dt;
    angle += deltaAngle;
    if (angle > 360)
        angle -= 360;
    Celestial::move(); // move the children
}

// Calls the display list for the planet after performing the
// appropriate transformations.
void Planet::display()
{
    glPushMatrix();
    glRotatef(angle, 0, 1, 0);       // rotate around the sun
    glTranslatef(orbit, 0, 0);       // place it in orbit
    glColor3f(thisR, thisG, thisB);
    glCallList(thisId);
    for (int i=0; i<nrChildren; i++) // if we have satelites
        children[i]->display();
    glPopMatrix();
}
