/********************************************************************

  File:         main.cc 
  Author:       Dana Vrajitoru
  Project:      Maze game
  Last updated: April 2017.

  Main function for the gradient program.

********************************************************************/

#include "glheader.h"
#include <cstdlib>
#include "interface.h"

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    myinit();
    createObjects();
    glutMainLoop();
}
