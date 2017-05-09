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

// callback for key action
void key(int key, int x, int y);

// various application parameters
void myinit();

//detect key press
void keyPressed (unsigned char key, int x, int y);

//light source initilization
void lightInit();

//material for light source
void materialWhite();
#endif
