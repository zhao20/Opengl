/*************************************************************************
  FILE:   Earth.h
          The Earth class handling the creation, movement, and display of 
          the class, plus all the configurable settings.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#ifndef EARTH_H
#define EARTH_H

#include "Planet.h"

class Earth : public Planet {
private:
    
public:
    // Constructor : initialize the default values and initialize the
    // display list for the Earth.
    Earth();

};

#endif
