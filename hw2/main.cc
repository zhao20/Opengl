/********************************************************************
  File:         main.cc 
  Author:       Dana Vrajitoru
  Project:      An OpenGL program creating an optical illusion
  Last updated: January 23, 2017.

  Main function for the illusion program.

********************************************************************/

#include "glheader.h"
#include "interface.h"

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    createWindowGUI();
    myinit();
    glutMainLoop();
}
