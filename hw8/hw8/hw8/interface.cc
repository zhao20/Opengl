/*************************************************************************
 FILE:   interface.cc
 Everything related to the display and the interface.

 Author: Dana Vrajitoru, IUSB
 Class:  C481 B581 Computer Graphics
 **************************************************************************/

#include <cstdlib>
#include "glheader.h"
#include "interface.h"
#include "trackball.h"
#include "surface.h"

extern float trans[];
int winWidth=600, winHeight=600;
int listId;

	// Callback for a display event.
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

		//glPolygonMode(GL_FRONT, GL_FILL);
	lightInit();
	glCallList(listId);
		//material_blue();
		//glutSolidTorus(1, 2, 10, 10);
	glutSwapBuffers(); 
}

	// Callback for an event resizing the window.
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

	// Callback for a keyboard event.
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

	// Defining one particlar set of material properties that make the
	// objects following a call to this function blue and kind of shiny.
void materialBlue()
{
	GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat matDiffuse[]  = {0.0, 0.0, 0.5, 1.0};
	GLfloat mat_ambient[] = {0.5, 0.5, 1.0, 1.0};
	GLfloat matShininess  = {2.5};

		// define material proerties for front face of all polygons

	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
}

	// Defining one particlar set of material properties that make the
	// objects following a call to this function blue and kind of shiny.
void materialBlack()
{	//RGB black
	GLfloat matSpecular[] = {0.0, 0.0, 1.0, 1.0};
	GLfloat matDiffuse[]  = {0.0, 0.0, 1.0, 1.0};
	GLfloat mat_ambient[] = {0.0, 0.0, 1.0, 1.0};
	GLfloat matShininess  = {2.5};

		// define material proerties for front face of all polygons
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
}

	// Defining one particlar set of material properties that make the
	// objects following a call to this function blue and kind of shiny.
void materialWhite()
{	//RGB white
	GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat matDiffuse[]  = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat matShininess  = {2.5};

		// define material proerties for front face of all polygons
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
}
	// Defining one particlar set of material properties that make the
	// objects following a call to this function red and kind of shiny.
void materialRed()
{	//rgb red
	GLfloat matSpecular[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat matDiffuse[]  = {1.0, 0.0, 0.0, 1.0};
	GLfloat mat_ambient[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat matShininess  = {2.5};

		// define material proerties for front face of all polygons
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, matShininess);
}

	// Initialize one light source.
void lightInit()
{
	GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
	GLfloat lightDiffuse[]  = {1.0, 0.5, 0.5, 1.0};
	GLfloat lightSpecular[] = {0.1, 0.1, 0.1, 1.0};
	GLfloat lightPosition[] = {0.0, 5.0, -2.0, 1.0};

		// set up ambient, diffuse, and specular components for light 0

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glShadeModel(GL_SMOOTH); /*enable smooth shading */
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_LIGHT0);  /* enable light 0 */
	glEnable(GL_DEPTH_TEST); /* enable z buffer */
		//glEnable(GL_COLOR_MATERIAL);
		//glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

	glClearColor (0.1, 0.1, 0.1, 1.0);
	glColor3f (1, 0.0, 0.0);
}

	// Create the display list for the scene.
void createDisplayList()
{
	Point3f p;
		//top of mushroom
	vector3f topPoints, topNormals;
	matrix3f topSurfacePt, topSurfaceNm;
		//bottom of mushroom
	vector3f bottomPoints, bottomNormals;
	matrix3f btSurfacePt, btSurfaceNm;
		//stem of mushroom
	vector3f stemPoints, stemNormals;
	matrix3f stSurfacePt, stSurfaceNm;

		//stem points
	p.setData(0,-3,0);
	stemPoints.push_back(p);
	p.setData(1,-3,0);
	stemPoints.push_back(p);
	p.setData(1,-1,0);
	stemPoints.push_back(p);

		//bottom points
	p.setData(1,-1, 0);
	bottomPoints.push_back(p);
	p.setData(4,-1, 0);
	bottomPoints.push_back(p);

		//top points
	p.setData(4, -1, 0);
	topPoints.push_back(p);
	p.setData(3.9,-0.9,0);
	topPoints.push_back(p);
	p.setData(3.0, -0.7, 0);
	topPoints.push_back(p);
	p.setData(2.5, -0.5, 0);
	topPoints.push_back(p);
	p.setData(1.5, -0.3, 0);
	topPoints.push_back(p);
	p.setData(0.5, -0.1, 0);
	topPoints.push_back(p);
	p.setData(0, 0.0, 0);
	topPoints.push_back(p);

		//generate list ID
	listId = glGenLists(1);

		// Create the display list.
	glNewList(listId, GL_COMPILE);
	glColor3f(1.0, 1.0, 0.0);

		//draw top part
	materialRed();
	computeNormalsXy(topPoints, topNormals);
	rotationSurfaceY(topPoints, topNormals, topSurfacePt, topSurfaceNm);
	drawSurface(topSurfacePt, topSurfaceNm);
		//drawLineStrip(bottlePoints);
		//draw bottom
	materialBlack();
	computeNormalsXy(bottomPoints, bottomNormals);
	rotationSurfaceY(bottomPoints, bottomPoints, btSurfacePt,btSurfaceNm);
	drawSurface(btSurfacePt, btSurfaceNm);

		//draw stem
	materialWhite();
	computeNormalsXy(stemPoints, stemNormals);
	rotationSurfaceY(stemPoints, stemNormals, stSurfacePt, stSurfaceNm);
	drawSurface(stSurfacePt, stSurfaceNm);



		//draw ring on the top of mushroom
	Point3f r;
	vector3f ringPoints, ringNormals;
	matrix3f ringSurfacePt, ringSurfaceNm;
	r.setData(3,2.5, 0);
	ringPoints.push_back(r);
	r.setData(4,2.5, 0);
	ringPoints.push_back(r);
	r.setData(4,3, 0);
	ringPoints.push_back(r);
	r.setData(3,3, 0);
	ringPoints.push_back(r);
	r.setData(3,2.5, 0);
	ringPoints.push_back(r);

		//setup color and light
	materialRed();
		//draw ring
	computeNormalsXy(ringPoints, ringNormals);
	rotationSurfaceY(ringPoints, ringNormals, ringSurfacePt, ringSurfaceNm);
	drawSurface(ringSurfacePt, ringSurfaceNm);
	
	glEndList();
}
