/*************************************************************************
  FILE:   Saturn.h
          The Saturn class handling the creation, movement, and display of
          the class, plus all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#ifndef VENUS_H
#define VENUS_H

#include "Planet.h"

class Saturn : public Planet {
private:
    
public:
    // Constructor : initialize the default values and initialize the
    // display list for the Earth.
    Saturn();

	void initDisplayList();

};

#endif
