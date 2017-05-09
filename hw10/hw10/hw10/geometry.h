/*************************************************************************
  FILE:   geometry.h
          Functions creating the geometry of the objects in the scene and 
          drawing them.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "Point3f.h"

const int MESH_ID = 1;
const int MESH_ID2 = 2;
// Read .raw file as a triangle strip
void loadRawFile(char *filename);

// Read .raw file as a triangle strip
void loadObjectFile(char *filename);

// a version of drawing the window that uses the display list
void draw1();

// a version of drawing the window that uses the matrix
void draw2();

// a version of drawing the window that uses the normalized matrix
void draw3();

//calculate the normalize value
void computeNormalsXy(vector3f &vPoints, vector3f &normals);


#endif
