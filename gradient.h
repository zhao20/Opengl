/********************************************************************
  File: gradient.cc 
  Author:       Dana Vrajitoru
  Project:      Simple gradient program
  Last updated: January 9, 2017.

  Drawing several gradients using simple lines.

********************************************************************/

#ifndef GRADIENT_H
#define GRADIENT_H


// display a vertical gradient going from the bg color on the left to
// the fg color on the right
void verticalGrad(float bg[], float fg[], 
                  float start[], float end[]);

// display a vertical gradient made of horizontal lines of varying color
void verticalGrad1(float bg[], float fg[], 
                   float start[], float end[]);

// display a horizontal gradient going from the bg color on the bottom to
// the fg color on the top
void horizontalGrad(float bg[], float fg[], 
                    float start[], float end[]);

// display a square gradient going from the bg color in the center to
// the fg color on the outside
void squareGrad(float bg[], float fg[], 
                float start[], float end[]);

// display a main diagonal gradient going from the bg color in the bottom
// left corner to the fg color in the top right corner
void diagonalGrad(float bg[], float fg[], 
                  float start[], float end[]);

// display a custom gradient
void customGrad(float bg[], float fg[], 
                float start[], float end[]);

#endif
