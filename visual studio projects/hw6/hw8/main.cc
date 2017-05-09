/*************************************************************************
FILE:   main.cc 
A program displaying a rotation surface.

Author: Dana Vrajitoru, IUSB
Class:  C481 B581 Computer Graphics
**************************************************************************/

#include <cstdlib>
#include "glheader.h"
#include "interface.h"
#include "trackball.h"

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Rotation surface");

    /* need both double buffering and z buffer */

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinObject);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    //  glutKeyboardFunc(key);
    glutSpecialFunc(key);

    glEnable(GL_DEPTH_TEST); // z buffer
	glEnable(GL_NORMALIZE);	//en
    createDisplayList();
    lightInit();

    glClearColor (0.1, 0.1, 0.1, 1.0);
    glColor3f (1, 0.0, 0.0);

    glutMainLoop();
}
