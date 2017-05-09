/*************************************************************************
  FILE:   interface.h
          Everything related to the display and the interface.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#ifndef INTERFACE_H
#define INTERFACE_H

#include "Point3f.h"

// Callback for a display event.
void display();

// Callback for an event resizing the window.
void myReshape(int w, int h);

// Callback for a keyboard event.
void key(int key, int x, int y);

// Defining one particlar set of material properties that make the
// objects following a call to this function blue and kind of shiny.
void materialBlue();

// Initialize one light source.
void lightInit();

// Create the display list for the scene.
void createDisplayList();

#endif

