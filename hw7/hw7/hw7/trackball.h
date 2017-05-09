/******************************************************************************
* FILE:   trackball.h
*         Some useful functions to define a trackball mouse interface.
*
* Author: Adapted by Dana Vrajitoru from the E. Angel textbook cd.
* Class:  C481 B581 Computer Graphics
******************************************************************************/

#ifndef TRACKBALL_H
#define TRACKBALL_H

void trackballPtov(int x, int y, int width, int height, float v[3]);

void startMotion(int x, int y);

void stopMotion(int x, int y);

// To be called from the display to apply the rotation defined by the
// trackball.
void applyRotation();

// Continues to spin the object if it has to. To be used as the iddle
// function. The applyRotation is calling it too.
void spinObject();

// To be called when the user click a mouse button.
void mouseButton(int button, int state, int x, int y);

// To be called when the mouse is moving.
void mouseMotion(int x, int y);

#endif
