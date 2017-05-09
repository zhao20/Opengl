/********************************************************************

  File:          Box.cc
  Author:        Dana Vrajitoru

  Description:   A class handling a frame-aligned boxcube
  Project:       A sprite moving through a maze application.

  Last updated:  April 2017

********************************************************************/

#include <cstdlib>
#include <iostream>
using namespace std;
#include "glheader.h"
#include "Box.h"

GLfloat coords[][3] = {{-1.0,-1.0,-1.0}, {1.0,-1.0,-1.0},
                         {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, 
                         {-1.0,-1.0,1.0}, {1.0,-1.0,1.0}, 
                         {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat normals[][3] = {{-1.0,-1.0,-1.0}, {1.0,-1.0,-1.0},
                        {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, 
                        {-1.0,-1.0,1.0}, {1.0,-1.0,1.0}, 
                        {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

// constructor with the dimensions of the box
Box::Box(float wval, float hval, float dval)
    :texture(NULL), widthT(0), heightT(0), tileX(1), tileY(1)
{
    for (int i=0; i<8; i++) {
        // scale the coordinates by the dimensions
        vertices[i][0] = 0.5*wval*(coords[i][0]+1.0); 
        vertices[i][1] = 0.5*hval*(coords[i][1]+1.0);
        vertices[i][2] = 0.5*dval*(coords[i][2]+1.0);
    }
    // store the dimensions in attributes
    width = wval;
    height = hval;
    depth = dval;
}

// destructor: delete the texture if we have it
Box::~Box()
{
    if (texture)
        delete [] texture; // it's an array
}

// set the number of tiles over x and y for the texture
void Box::setTiling(int x, int y)
{
    tileX = x;
    tileY = y;
}

// draws a polygon from 4 points
void Box::polygon(int a, int b, int c , int d)
{
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}

// draws a polygon from 4 points with normals
void Box::polygonNormals(int a, int b, int c , int d)
{
    glBegin(GL_POLYGON);
    glNormal3fv(normals[a]);
    glVertex3fv(vertices[a]);
    glNormal3fv(normals[b]);
    glVertex3fv(vertices[b]);
    glNormal3fv(normals[c]);
    glVertex3fv(vertices[c]);
    glNormal3fv(normals[d]);
    glVertex3fv(vertices[d]);
    glEnd();
}

// draws a polygon from 4 points with normals and texture
void Box::polygonTexture(int a, int b, int c , int d)
{
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0); 
    glNormal3fv(normals[a]);
    glVertex3fv(vertices[a]);
    glTexCoord2f(0, 1*tileY); 
    glNormal3fv(normals[b]);
    glVertex3fv(vertices[b]);
    glTexCoord2f(1*tileX, 1*tileY); 
    glNormal3fv(normals[c]);
    glVertex3fv(vertices[c]);
    glTexCoord2f(1*tileX, 0); 
    glNormal3fv(normals[d]);
    glVertex3fv(vertices[d]);
    glEnd();
}

// create the display list in simple mode
void Box::draw()
{

    thisId = glGenLists(1); // Gets the next available id for a
                            // display list.

    glNewList(thisId, GL_COMPILE);
    polygon(0, 3, 2, 1);
    polygon(2, 3, 7, 6);
    polygon(0, 4, 7, 3);
    polygon(1, 2, 6, 5);
    polygon(4, 5, 6, 7);
    polygon(0, 1, 5, 4);
    glEndList();
}

// create the display list with normals
void Box::drawNormals()
{

    thisId = glGenLists(1); // Gets the next available id for a
                            // display list.

    glNewList(thisId, GL_COMPILE);
    polygonNormals(0, 3, 2, 1);
    polygonNormals(2, 3, 7, 6);
    polygonNormals(0, 4, 7, 3);
    polygonNormals(1, 2, 6, 5);
    polygonNormals(4, 5, 6, 7);
    polygonNormals(0, 1, 5, 4);
    glEndList();
}

// create the display list with normals and texture
void Box::drawTexture()
{

    thisId = glGenLists(1); // Gets the next available id for a
                            // display list.

    glNewList(thisId, GL_COMPILE);
    polygonTexture(0, 3, 2, 1);
    polygonTexture(2, 3, 7, 6);
    polygonTexture(0, 4, 7, 3);
    polygonTexture(1, 2, 6, 5);
    polygonTexture(4, 5, 6, 7);
    polygonTexture(0, 1, 5, 4);
    glEndList();
}

// Calls the display list for the box. Transformations, colors, and
// textures are handled elsewhere.
void Box::display()
{
    glCallList(thisId);
    //drawTexture();
}
