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

#ifdef __APPLE__

#include <GLUT/glut.h>

#else

#include <GL/glut.h>

#ifdef WIN_GL

#define M_PI 3.14159265359

#endif

#endif

#endif
