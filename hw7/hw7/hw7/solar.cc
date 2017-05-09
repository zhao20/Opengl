/*************************************************************************
  FILE:   solar.cc 
          A program displaying the solar system composed of the sun and 
          the earth.

  Author: Dana Vrajitoru, IUSB
  Class:  C481 B581 Computer Graphics
**************************************************************************/

#include <cstdlib>
//#include <GL/glut.h>
#include "glheader.h"
#include "trackball.h"
#include "Sun.h"
#include <iostream>
using namespace std;

//GLUquadricObj *obj;
//static GLfloat theta[] = {0.0,0.0,0.0};
//static GLint axis = 2;
static GLfloat trans[] = {0.0,0.0,0.45};
int winWidth=800, winHeight=1200;
int timerSpeed = 40;
Sun *solar = NULL;
GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};

void display()
{
    // Apply the trackball transformation.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 3.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPopMatrix();
    applyRotation();
    glPushMatrix();

    // The translation of the whole scene.
    glTranslatef(trans[0], trans[1], 0);
    glScalef(trans[2], trans[2], trans[2]);

    // so that the light follows the sun
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Move the solar system then redisplay.
    solar->move();
    solar->display();

    glutSwapBuffers();
}

static void timerCallback (int value) 
{ 
    display();
    // glutPostRedisplay(); seems to work without it.
    if (value) 
        glutTimerFunc(timerSpeed, timerCallback, value); 
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, w/h, 0.5, 40.0); 
    /*  if (w<=h) 
        glFrustum(-10.0, 10.0, -10.0 * (GLfloat) h/ (GLfloat) w, 
        10.0* (GLfloat) h / (GLfloat) w, -10.0, 20.0);
        else 
        glFrustum(-10.0, 10.0, -10.0 * (GLfloat) w/ (GLfloat) h, 
        10.0* (GLfloat) w / (GLfloat) h, -10.0, 20.0);
    */
    glMatrixMode(GL_MODELVIEW);
    winWidth = w;
    winHeight = h;
}

void key(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_LEFT:
        trans[0] -= 0.1;
        break;
    case GLUT_KEY_RIGHT:
        trans[0] += 0.1;
        break;
    case GLUT_KEY_UP:
        trans[1] += 0.1;
        break;
    case GLUT_KEY_DOWN:
        trans[1] -= 0.1;
        break;
    case GLUT_KEY_PAGE_UP:
        trans[2] += 0.1;
        break;
    case GLUT_KEY_PAGE_DOWN:
        trans[2] -= 0.1;
    }
    display();
}


void lightInit()
{
    GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[]={0.0, 0.0, 1.0, 1.0};
    GLfloat mat_ambient[]={0.0, 0.5, 1.0, 1.0};
    GLfloat mat_shininess={100.0};
    GLfloat light_ambient[]={0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};

    /* set up ambient, diffuse, and specular components for light 0 */

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);


    /* define material proerties for front face of all polygons */

    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glShadeModel(GL_SMOOTH); /*enable smooth shading */
    glEnable(GL_LIGHTING); /* enable lighting */
    glEnable(GL_LIGHT0);  /* enable light 0 */
    glEnable(GL_DEPTH_TEST); /* enable z buffer */
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

    glClearColor (0.1, 0.1, 0.1, 1.0);
    glColor3f (1, 0.0, 0.0);
}

int main(int argc, char **argv)
{
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("The solar system");

    solar = new Sun();

    /* need both double buffering and z buffer */

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    //glutIdleFunc(display);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    //  glutKeyboardFunc(key);
    glutSpecialFunc(key);


    glEnable(GL_DEPTH_TEST); // z buffer

    lightInit();
 
    glClearColor (0.1, 0.1, 0.1, 1.0);
    glColor3f (1, 0.0, 0.0);

    glutTimerFunc(timerSpeed, timerCallback, 1); 

    glutMainLoop();
}
