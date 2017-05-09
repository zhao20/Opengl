/********************************************************************
  File:         interface.h
  Author:       Dana Vrajitoru
  Project:      Optical illusion
  Last updated: January 23, 2017.

  Interface functions for the program.

********************************************************************/

#ifndef INTERFACE_H
#define INTERFACE_H

// Create a window and set up the GUI functions
void createWindowGUI();

// Defining some of the application parameters
void myinit();

// To be called whenever the window is resized.
void myResize(int w, int h);

// Callback function for redrawing the window 
void display(void);

// Callback function for an Ascii key being pressed
void key(unsigned char key, int x, int y);

// Callback function for a special key being pressed
void spkey(int key, int x, int y);

#endif
