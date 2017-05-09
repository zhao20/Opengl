/********************************************************************
  File:         glheader.h 
  Author:       Dana Vrajitoru
  Project:      An OpenGL program creating an optical illusion
  Last updated: January 23, 2017.

  Which GL and GLUT headers to include based on the operating system

********************************************************************/

#ifndef GLHEADER_H
#define GLHEADER_H

#define LINUX_GL
//#define MACOS_GL
//#define WIN_GL

#ifdef MACOS_GL

#include <GLUT/glut.h>

#else

#include <GL/glut.h>

#endif

#endif
