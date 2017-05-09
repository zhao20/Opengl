/* cube.c        */
/* Rotating cube with color interpolation */
/* E. Angel, Interactive Computer Graphics */
/* A Top-Down Approach with OpenGL, Third Edition */
/* Addison-Wesley Longman, 2003 */

/* Demonstration of use of homogeneous coordinate 
   transformations and simple data structure for representing
   cube from Chapter 4 */

/* Colors are assigned to the vertices */
/* Mouse buttons control direction of rotation */
/* Modified by D. Vrajitoru, February 17, 2017 */

#include <cstdlib>
//#include <GL/glut.h>
#include "glheader.h"
#include <ctime>

GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
			 {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
			 {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},
		       {1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}, 
		       {1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};

// draw a polygon via list of vertices */
void polygon(int a, int b, int c , int d)
{
    glBegin(GL_POLYGON);
    glColor3fv(colors[a]);
    glVertex3fv(vertices[a]);
    glColor3fv(colors[b]);
    glVertex3fv(vertices[b]);
    glColor3fv(colors[c]);
    glVertex3fv(vertices[c]);
    glColor3fv(colors[d]);
    glVertex3fv(vertices[d]);
    glEnd();
}

// map vertices to faces 
void colorcube(void)
{

    polygon(0,3,2,1);
    polygon(2,3,7,6);
    polygon(0,4,7,3);
    polygon(1,2,6,5);
    polygon(4,5,6,7);
    polygon(0,1,5,4);
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;

// display callback, clear frame buffer and z buffer,
// rotate cube and draw, swap buffers 
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    
    colorcube();
    
    glFlush();
    glutSwapBuffers();
}

// Idle callback, spin cube 2 degrees about selected axis 
void spinCube(int value)
{

    theta[axis] += 2.0;
    if( theta[axis] > 360.0 ) 
        theta[axis] -= 360.0;
    
    /* display(); */
    glutPostRedisplay();
    glutTimerFunc(50, spinCube, 1);
}

// mouse callback, selects an axis about which to rotate */
void mouse(int btn, int state, int x, int y)
{ 

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
        axis = 0;
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
        axis = 1;
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
        axis = 2;
}

// callback for resizing the window
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
                2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
                2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

// main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    /* need both double buffering and z buffer */

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("colorcube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    //glutIdleFunc(spinCube);
    glutTimerFunc(50, spinCube, 1);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
    glutMainLoop();
    return 0;
}
