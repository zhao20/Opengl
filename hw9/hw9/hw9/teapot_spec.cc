/***************************************************

  E. Angel, Interactive Computer Graphics 
  A Top-Down Approach with OpenGL, Third Edition 
  Addison-Wesley Longman, 2003 

  Modified by D. Vrajitoru, 2017

/***************************************************/

#include <cstdlib>
#include "glheader.h"
#include "stdio.h"

GLUquadricObj *obj;
static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLint axis = 2;
static GLfloat trans[] = {0.0, 0.0, 1};
	//ligth positon array
static GLfloat lightPos[] = {3.0, 0.0, 0.0};
static GLfloat angle = 0;	//light rotate angle

// display callback, clear frame buffer and z buffer,
// rotate object and draw, swap buffers 
void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 3.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glTranslatef(trans[0], trans[1], 0);
    glScalef(trans[2], trans[2], trans[2]);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    //glScalef(1.2, 1.0, 0.8);

    // glutWireIcosahedron();
    // glutWireDodecahedron();
    // gluSphere(obj, 1.0, 12, 12);
    //	gluCylinder(obj, 1.0, 0.5, 1.0, 12, 12); 
    glPushMatrix();
    glRotatef(270, 1.0, 0, 0);
    glTranslatef(0, 0, -0.75);
    glColor3f(0.5, 0.5, 1.0);

    gluDisk(obj, 0, 10.0, 20, 20);
    glPopMatrix();
    // gluPartialDisk( obj, 0.5, 1.0, 10, 10, 0.0, 45.0);
    glColor3f(1.0, 0.5, 1.0);

    glutSolidTeapot(1.0);
    // glutWireTorus(0.5, 1.0, 10, 10);
    // glutWireCone(1.0, 1.0, 10, 10);

	glPushMatrix();
	glTranslated(2.5,-0.05,0.0);
	glRotated(-90, -0.1, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
		//top part of the little cup
	glutSolidCone(.2, 0.7, 50, 50);
	glTranslated(0,0,0.7);
	glRotated(180, -0.1, 0.0, 0.0);
		//bottom part of the cup
	glutSolidCone(.1, 0.3, 50, 50);
	glTranslated(0,0,0.01);
		//bottom saucer
	gluDisk(gluNewQuadric(), 0,1, 50, 20);
	glPopMatrix();

    glutSwapBuffers();
}

// Idle callback, spin cube 2 degrees about selected axis 
void spinObject()
{
    theta[axis] += 1.0;
    if( theta[axis] > 360.0 ) 
        theta[axis] -= 360.0;
    glutPostRedisplay();
}


	// Idle callback, spin light 5 degrees about selected axis
void spinLightSource()
{
	glLoadIdentity();
	glPushMatrix();

	angle += 5; //increase angle each call
	// reset angle great than 360
	if(angle >= 360.0f)
		angle = 0.0f;
		//rotate on z axis because teapot has been rotate 90 degree before
	glRotated(angle, 0.0, 0.0, 1.0);
		//update postion
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glPopMatrix();
	glutPostRedisplay();

}

	// mouse callback, selects an axis about which to rotate
void mouse(int btn, int state, int x, int y)
{
    if (state == GLUT_DOWN)
        glutIdleFunc(spinObject);
    else
        glutIdleFunc(spinLightSource);

    switch (btn) {
    case GLUT_LEFT_BUTTON:
        axis = 0;
        break;
    case GLUT_MIDDLE_BUTTON:
        axis = 1;
        break;
    case GLUT_RIGHT_BUTTON:
        axis = 2;
    }
}

// resizing the window
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, w/h, 2.0, 40.0); 
    /*  if (w<=h) 
    glFrustum(-10.0, 10.0, -10.0 * (GLfloat) h/ (GLfloat) w, 
    10.0* (GLfloat) h / (GLfloat) w, -10.0, 20.0);
    else 
    glFrustum(-10.0, 10.0, -10.0 * (GLfloat) w/ (GLfloat) h, 
    10.0* (GLfloat) w / (GLfloat) h, -10.0, 20.0);
    */
    glMatrixMode(GL_MODELVIEW);
}

// key callback
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

// set up ambient, diffuse, and specular components for light 0 
void light0()
{
    
    GLfloat lightAmbient[]={0.5, 0.5, 0.5, 1.0};
    GLfloat lightDiffuse[]={0.5, 0.5, 0.5, 1.0};
    GLfloat lightSpecular[]={1.0, 1.0, 1.0, 1.0};
    GLfloat lightPosition[]={0.0, 0.0, 0.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

// set up ambient, diffuse, and specular components for light 0
void light1()
{

	GLfloat lightAmbient[]={0.1, 0.1, 0.1, 1.0};
	GLfloat lightDiffuse[]={0.1, 0.1, 0.1, 1.0};
	GLfloat lightSpecular[]={1.0, 1.0, 1.0, 1.0};
		//GLfloat lightPosition[]={0.0, 0.0, 0.0};

	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
}

void myinit()
{
    GLfloat matSpecular[]={0.5, 0.5, 0.5, 1.0};
    GLfloat matDiffuse[]={0.0, 0.0, 1.0, 1.0};
    GLfloat matAmbient[]={0.0, 0.5, 1.0, 1.0};
    GLfloat matShininess={100.0};
		//light0();
		light1();

    // define material proerties for front face of all polygons 

    //glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    //glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    //glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    glShadeModel(GL_SMOOTH); // enable smooth shading 
    glEnable(GL_LIGHTING);   // enable lighting 
    glEnable(GL_LIGHT0);     // enable light 0
	glEnable(GL_LIGHT1);     // enable light 1
    glEnable(GL_DEPTH_TEST); // enable z buffer 
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMateriali(GL_FRONT, GL_SHININESS, 50);

    glClearColor (1.0, 1.0, 1.0, 1.0);
    glColor3f (1, 0.0, 0.0);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("object");
    myinit();

    // need both double buffering and z buffer 

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinLightSource);
    glutMouseFunc(mouse);
    //  glutKeyboardFunc(key);
    glutSpecialFunc(key);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_FILL);

    glutMainLoop();

    return 0;
}
