/********************************************************************
  File:         main.cc 
  Author:       Dana Vrajitoru
  Project:      Simple gradient program
  Last updated: February 3, 2011.

  Main function for the gradient program.

********************************************************************/

#include "glheader.h"
#include <cstdlib>
#include "brickbreak.h"

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  initWindowGui();
  myinit();
  glutMainLoop();
}
