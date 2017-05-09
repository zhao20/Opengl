/*************************************************************************
  FILE:   Celestial.h
          The Celestial class handling the creation, movement, and
          display of a base class representing a celestial body, plus
          all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#ifndef CELESTIAL_H
#define CELESTIAL_H

class Celestial {
protected:
    // local properties
    int thisId;
    float radius;
    float thisR, thisG, thisB;

    // delta T
    float dt;

    // scene tree structure: an array of pointers to children objects 
    Celestial **children;
    int nrChildren;

public:

    // Constructor : initialize the default values and initialize the
    // display list for the celestial body.
    Celestial(float rad = 1);

    // set the color so that we can use it for several planets
    void setColor(float r, float g, float b);

    // initialize the content of the display list
    virtual void initDisplayList();

    // Performs one movement of the sun in delta t.
    virtual void move();

    // Calls the display list for the celestial body after performing the
    // appropriate transformations.
    virtual void display();
};

typedef Celestial * CelestialPtr;

#endif
