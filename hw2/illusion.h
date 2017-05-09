/********************************************************************
  File:         illusion.h
  Author:       Dana Vrajitoru
  Project:      Optical illusion
  Last updated: January 23, 2017.

  Functions creating the content of the window

********************************************************************/

#ifndef ILLUSION_H
#define ILLUSION_H


// Display an optical illusion that creates a lens effect by drawing
// lines from the sides of the window towards the center at increasing
// distances from each other
void lensIllusion(float gap, float color[], float width, float height);

#endif
