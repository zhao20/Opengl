/*************************************************************************
  FILE:   interface.h
          Interface callback functions, window manipulation, display.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#ifndef INTERFACE_H
#define INTERFACE_H

// display function, calls the display list
void display(void);

// callback for a mouse event, selects an axis about which to rotate
void mouse(int btn, int state, int x, int y);

// callback for the window size changing
void myReshape(int w, int h);

// callback for special key action
void spkey(int key, int x, int y);
// callback for key action
void key(unsigned char key, int x, int y);

// set up ambient, diffuse, and specular components for light 0 
void light0();

// Defining one particlar set of material properties that make the
// objects following a call to this function blue and kind of shiny.
void materialBlue();

// create a texture from a pixel data buffer
void makeTexture(char *buffer, int width, int height);

// create the scene objects
void createObjects();

// various application parameters
void myinit();

#endif
