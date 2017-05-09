/********************************************************************
  File:         interface.h
  Author:       Dana Vrajitoru
  Project:      A fractal program
  Last updated: January 30, 2017.

  Interface functions for the fractal program.

********************************************************************/

#ifndef INTERFACE_H
#define INTERFACE_H

typedef float Point2[2];

// Create a window and set up the GUI functions
void createWindowGUI();

// Application parameters
void myinit();

// To be called whenever the window is resized.
void myResize(int w, int h);

// Callback function for the display
void display(void);

// Callback function for an Ascii key being pressed
void key(unsigned char key, int x, int y);

// Callback function for a special key being pressed
void spkey(int key, int x, int y);

#endif
