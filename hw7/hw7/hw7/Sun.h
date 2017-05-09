/*************************************************************************
  FILE:   Sun.h
          The Sun class handling the creation, movement, and display of 
          the class, plus all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#ifndef SUN_H
#define SUN_H

#include "Celestial.h"

class Sun: public Celestial {
private:
    
public:
    // Constructor : initialize the default values and initialize the
    // display list for the Sun.
    Sun();

    // initialize the content of the display list
    virtual void initDisplayList();
};

#endif
