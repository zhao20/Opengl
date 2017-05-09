/********************************************************************

  File:          Box.h
  Author:        Dana Vrajitoru

  Description:   A class handling a frame-aligned box
  Project:       A sprite moving through a maze application.

  Last updated:  April 2017

********************************************************************/


class Box {
public:

    GLfloat vertices[8][3];

    // texture data and dimensions
    char *texture;
    int widthT, heightT;
    int tileX, tileY;

    float width, height, depth; // dimensions
    int thisId;                 // id for a display list

    // constructor with the dimensions of the box
    Box(float wval = 1, float hval = 1, float dval = 1);

    // destructor: delete the texture if we have it
    ~Box();

    // set the number of tiles over x and y for the texture
    void setTiling(int x=1, int y=1);

    // create the display list in simple mode
    void draw();

    // create the display list with normals
    void drawNormals();

    // create the display list with normals and texture coordinates
    void drawTexture();

    // Calls the display list for the box. Transformations, colors,
    // and textures are handled elsewhere.
    void display();

    // draws a polygon from 4 points with normals
    void polygon(int a, int b, int c , int d);

    // draws a polygon from 4 points with normals
    void polygonNormals(int a, int b, int c , int d);

    // draws a polygon from 4 points with normals and texture
    void polygonTexture(int a, int b, int c , int d);
};
