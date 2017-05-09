/********************************************************************
  File:         main.cc 
  Author:       Dana Vrajitoru
  Project:      A fractal program
  Last updated: January 30, 2017.

  Main function for the fractal program.

********************************************************************/

#include "glheader.h"
#include <cstdlib>
#include "interface.h"
#include "sierpinski.h"


int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  createWindowGUI();
  myinit();
  glutMainLoop();
}
