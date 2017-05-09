/* cubeview.c          */
/* E. Angel, Interactive Computer Graphics */
/* A Top-Down Approach with OpenGL, Third Edition */
/* Addison-Wesley Longman, 2003 */
/* Rotating cube with viewer movement from Chapter 5 */
/* Cube definition and display similar to rotating--cube program */

/* We use the Lookat function in the display callback to point
   the viewer, whose position can be altered by the x,X,y,Y,z, and Z keys.
   The perspective view is set in the reshape callback 

   Modified by D. Vrajitoru, February 17, 2017. 
*/

#include <cstdlib>
#include "glheader.h"
//#include <GL/glut.h>

	//out cude matrix
GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
			 {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
			 {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};
	//inner cude matrix
GLfloat smallVertices[][3] = {{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},
	{0.5,0.5,-0.5}, {-0.5,0.5,-0.5}, {-0.5,-0.5,0.5},
	{0.5,-0.5,0.5}, {0.5,0.5,0.5}, {-0.5,0.5,0.5}};

GLfloat normals[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
			{1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
			{1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

GLfloat colors[][3] = {{0.0,0.0,0.0},{1.0,0.0,0.0},
		       {1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}, 
		       {1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};

// draws a polygon from 4 points and matrix
void polygon(int a, int b, int c , int d, GLfloat vertice[][3])
{
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glNormal3fv(normals[a]);
	glVertex3fv(vertice[a]);
	glColor3fv(colors[b]);
	glNormal3fv(normals[b]);
	glVertex3fv(vertice[b]);
	glColor3fv(colors[c]);
	glNormal3fv(normals[c]);
	glVertex3fv(vertice[c]);
	glColor3fv(colors[d]);
	glNormal3fv(normals[d]);
	glVertex3fv(vertice[d]);
	glEnd();

}
	//draw a polygon from same edges of both cubes.
void polygonConnection(int a, int b, GLfloat ver1[][3], GLfloat ver2[][3]){

	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glNormal3fv(normals[a]);
		//outer cube edge start point
	glVertex3fv(ver1[a]);
	glColor3fv(colors[b]);
	glNormal3fv(normals[b]);
		//outer cube edge ending points
	glVertex3fv(ver1[b]);
		//inner cude ending point
	glVertex3fv(ver2[b]);
		//inner cude starting point
	glVertex3fv(ver2[a]);
	glEnd();
	
}
// draws the cubes
void colorcube()
{
		//outter cube
    polygon(0,3,2,1, vertices);
    polygon(2,3,7,6, vertices);
    polygon(0,4,7,3, vertices);
    polygon(1,2,6,5, vertices);
    polygon(4,5,6,7, vertices);
    polygon(0,1,5,4, vertices);
		//inner cube
	polygon(0,3,2,1, smallVertices);
	polygon(2,3,7,6, smallVertices);
	polygon(0,4,7,3, smallVertices);
	polygon(1,2,6,5, smallVertices);
	polygon(4,5,6,7, smallVertices);
	polygon(0,1,5,4, smallVertices);
		//connection between two cubes
	polygonConnection(0, 3, vertices, smallVertices);
	polygonConnection(1, 2, vertices, smallVertices);
	polygonConnection(5, 6, vertices, smallVertices);
	polygonConnection(4, 7, vertices, smallVertices);
}


static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
	//the viewer location become constant
static const GLdouble viewer[]= {0.0, 0.0, 5.0}; /* initial viewer location */
float tranx = 0.0, trany = 0.0, tranz = 0.0;	//translate points


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.3, .2, .1, 1);	//background

    /* Update viewer position in modelview matrix */

    glLoadIdentity();
		//translate objects
	glTranslatef(tranx, trany, tranz);
    gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);


    /* rotate cube */

    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
		//draw cube
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

// mouse function: change the rotation axis
void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
        axis = 0;
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
        axis = 1;
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
        axis = 2;
    theta[axis] += 2.0;
    if ( theta[axis] > 360.0 ) 
        theta[axis] -= 360.0;
    display();
}

// Use x, X, y, Y, z, and Z keys to move viewer 
void keys(unsigned char key, int x, int y)
{
		//space key to reset position
	if(key == ' '){
		tranx = 0.0;
		trany = 0.0;
		tranz = 0.0;

	}
    if(key == 'x') 
			// viewer[0]-= 1.0;
		tranx -= 1.0;	//move left
    if(key == 'X')

			//viewer[0]+= 1.0;
		tranx += 1.0;	//move right
    if(key == 'y')
			//viewer[1]-= 1.0;
		trany -= 1.0;	//move down
    if(key == 'Y')
			//viewer[1]+= 1.0;
		trany += 1.0;	//move up
    if(key == 'z')
			//viewer[2]-= 1.0;
		tranz -= 1.0;	//zoom out
    if(key == 'Z') 
			//viewer[2]+= 1.0;
		tranz += 1.0;	//zoom in
    display();
}

// callback for resizing the window
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);

    /* Use a perspective view */
    
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    if(w<=h) 
        glFrustum(-2.0, 2.0, -2.0 * (GLfloat) h/ (GLfloat) w, 
                  2.0* (GLfloat) h / (GLfloat) w, 2.0, 20.0);
    else 
        glFrustum(-2.0, 2.0, -2.0 * (GLfloat) w/ (GLfloat) h, 
                  2.0* (GLfloat) w / (GLfloat) h, 2.0, 20.0);
    
    /* Or we can use gluPerspective */

    /* gluPerspective(45.0, w/h, -10.0, 10.0); */

    glMatrixMode(GL_MODELVIEW);
}

// main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("colorcube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
	glutTimerFunc(50, spinCube, 1);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keys);
    glEnable(GL_DEPTH_TEST);
	glLineWidth(3.0);
		//make polygan display as lines
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glutMainLoop();
}
