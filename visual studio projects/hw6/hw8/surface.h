/*************************************************************************
  FILE:   surface.h
          Functions used to generate curves and surfaces.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#ifndef SURFACE_H
#define SURFACE_H

#include "Point3f.h"

// Builds a circle in the xy plane with given center and radius made
// of 20 points. The first point is repeated a the end to create a
// loop. It stores the points and normals in the last two
// parameters. This is supposed to be drawn as a line strip.
void circleXy(float centerx, float centery, float centerz, float radius,
	          vector3f &points, vector3f &normals);

// Draws a curve as a line strip; we have no use for the normals for a
// line strip.
void drawLineStrip(vector3f &points);

// To be implemented by the students:

// Compute the normals for a curve in the xy plane. You can use the
// function orthogonalXy from the Point3f class. For each 2 line
// segments in a sequence, the normal should be the average of the two
// normals computed on each segment. If the first and last point are
// the same, then the normal in the first and last points should be
// averaged between the first and the last segment.
void computeNormalsXy(vector3f &points, vector3f &normals);

// Given a curve with normals in the xy plane, the function builds a
// rotation surface by rotating this curve around the Oy axis. It also
// computes the normals to the surface given the normals to the curve.
void rotationSurfaceY(vector3f &curvePt, vector3f &curveNm, 
                      matrix3f &surfacePt, matrix3f &surfaceNm);

// Draws the surface given as a grid of points as a sequence of
// triangle strips.
void drawSurface(matrix3f &surfacePt, matrix3f &surfaceNm);

#endif
