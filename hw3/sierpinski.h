/********************************************************************
  File:         sierpinski.h
  Author:       Dana Vrajitoru
                Based on the example provided in 
                E. Angel, Interactive Computer Graphics.
  Project:      An implementation of the Sierpinski gasket.
  Last updated: January 27, 2011.

  Drawing a fractal using triangles.

********************************************************************/

#ifndef SIERPINSKI_H
#define SIERPINSKI_H


typedef float point2[2];

// display one triangle
void triangle( point2 a, point2 b, point2 c);

// Implementation of the Sierpinski gasket by triangle subdivision
// using vertex numbers.
void divide_triangle(point2 a, point2 b, point2 c, int m);

// Implementation of the Sierpinski "carpet".
void carpet(point2 start, float width, int m);


void square(Point2 start, float width);




#endif
