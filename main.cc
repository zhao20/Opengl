/********************************************************************
  File:         main.cc 
  Author:       Dana Vrajitoru
  Project:      Simple gradient program
  Last updated: January 9, 2017.

  Main function for the gradient program.

********************************************************************/

#include <GLUT/glut.h>
#include <cstdlib>
#include <ctime>
#include "gradient.h"



void myinit();
void display(void);
void key(unsigned char key, int x, int y);
void spkey(int key, int x, int y);
void randomize();

enum Gtype {horizontal = 0, vertical, square, diagonal, other};

//Gtype gradType = vertical;
//Gtype gradType = horizontal;
//Gtype gradType = diagonal;
Gtype gradType = other;


const int width = 500, height = 500;
float start[2] = {0, 0}, end[2] = {width, height};

float black[3] = {0.0, 0.0, 0.0};
float white[3] = {1.0, 1.0, 1.0};
float red[3]   = {1.0, 0.0, 0.0};
float green[3] = {0.0, 1.0, 0.0};
float blue[3]  = {0.0, 0.0, 1.0};

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(width, height);
    glutCreateWindow("Gradient");
    glutDisplayFunc(display);
    //glutIdleFunc(display);
    glutKeyboardFunc(key);
    //glutSpecialFunc(spkey);
    //glutMouseFunc(mouse);
    myinit();
    srand(time(NULL));
    glutMainLoop();
}

// Application parameters
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glClearColor (0, 0, 0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2);
}

// Callback function for the display
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    switch (gradType) {
    case horizontal:
        horizontalGrad(red, blue, start, end);
        break;
    case vertical:
        verticalGrad(red, blue, start, end);
        break;
    case square:
        squareGrad(red, blue, start, end);
        break;
    case diagonal:
        diagonalGrad(red, blue, start, end);
        break;
    case other:
        customGrad(red, blue, start, end);
        break;
    }
    glFlush();
}

// Callback function for an Ascii key being pressed
void key(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
    case 'Q':
        exit(0);
    case ' ':
        randomize();
        glutPostRedisplay();
        break;
    }
}

// Callback function for a special key being pressed
void spkey(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_LEFT:
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        glutPostRedisplay();
        break;
    }
}

// Should randomize the gradient type and the two colors
void randomize()
{
    
    gradType = Gtype(rand()%5);
    red [0] =(rand()/(float)RAND_MAX);
    red [1] =(rand()/(float)RAND_MAX);
    red [2] =(rand()/(float)RAND_MAX);

    blue [0] =(rand()/(float)RAND_MAX);
    blue [1] =(rand()/(float)RAND_MAX);
    blue [2] =(rand()/(float)RAND_MAX);
    //red[] = new {(float)(rand()%RAND_MAX), (float)(rand()%RAND_MAX), (float)(rand()%RAND_MAX)};
    
    // To be completed by the student.
}
