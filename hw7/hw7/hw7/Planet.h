/*************************************************************************
  FILE:   Planet.h
          The Planet class handling the creation, movement, and display of 
          the class, plus all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#ifndef PLANET_H
#define PLANET_H

#include "Celestial.h"

class Planet : public Celestial {
protected:
    float speed, orbit, angle;
    
public:
    // Constructor : initialize the default values and initialize the
    // display list for the planet.
    Planet(float rad, float aSpeed=2, float orb=3, float startAngle=0);

    // Performs one movement of the planet in delta t.
    virtual void move();

    // Calls the display list for the planet after performing the
    // appropriate transformations.
    virtual void display();
};

#endif
