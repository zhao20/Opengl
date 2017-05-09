/******************************************************************************
 * FILE:   trackball.cc
 *         Some useful functions to define a trackball mouse interface.
 *
 * Author: Adapted by Dana Vrajitoru from the E. Angel textbook cd.
 * Class:  C481 B581 Computer Graphics
 ******************************************************************************/

#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;
//#include <GL/glut.h>
#include "glheader.h"
#include "trackball.h"

float lastPos[3] = {0.0F, 0.0F, 0.0F};
int curx, cury;
int startX, startY;

extern int 	winWidth, winHeight;

float 	angle = 0.0, axis[3];
bool 	trackingMouse = false;
bool 	redrawContinue = false;
bool    trackballMove = false;

// Determine a point on the 3D trackball based on the 2D position
void trackballPtov(int x, int y, int width, int height, float v[3])
{
    float d, a;

    // project x,y onto a hemi-sphere centered within width, height 
    v[0] = (2.0F*x - width) / width;
    v[1] = (height - 2.0F*y) / height;
    d = (float) sqrt(v[0]*v[0] + v[1]*v[1]);
    v[2] = (float) cos((M_PI/2.0F) * ((d < 1.0F) ? d : 1.0F));
    a = 1.0F / (float) sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] *= a;
    v[1] *= a;
    v[2] *= a;
}

// To be called when the mouse is moving.
void mouseMotion(int x, int y)
{
    float curPos[3], dx, dy, dz;

    trackballPtov(x, y, winWidth, winHeight, curPos);
    if(trackingMouse) {
        dx = curPos[0] - lastPos[0];
        dy = curPos[1] - lastPos[1];
        dz = curPos[2] - lastPos[2];

        if (dx || dy || dz) {
            angle = 0.25*90.0F * sqrt(dx*dx + dy*dy + dz*dz);

            axis[0] = lastPos[1]*curPos[2] - lastPos[2]*curPos[1];
            axis[1] = lastPos[2]*curPos[0] - lastPos[0]*curPos[2];
            axis[2] = lastPos[0]*curPos[1] - lastPos[1]*curPos[0];

            lastPos[0] = curPos[0];
            lastPos[1] = curPos[1];
            lastPos[2] = curPos[2];
        }
    } 
    glutPostRedisplay();
}

// Called when the user clicks to start the object's motion.
void startMotion(int x, int y)
{
    trackingMouse = true;
    redrawContinue = false;
    startX = x; 
    startY = y;
    curx = x; 
    cury = y;
    trackballPtov(x, winHeight-y, winWidth, winHeight, lastPos);
    trackballMove=true;
}

// Called when the user clicks to stop the object's motion.
void stopMotion(int x, int y)
{

    trackingMouse = false;

    if (startX != x || startY != y) {
        redrawContinue = true;
    } 
    else {
        angle = 0.0F;
        redrawContinue = false;
        trackballMove = false;
    }
}

// To be called from the display to apply the rotation defined by the
// trackball.
void applyRotation()
{
    // view transform 

    if (trackballMove) {
        glRotatef(angle, axis[0], axis[1], axis[2]);
    }
    spinObject();
}

// To be called when the user click or un-clicks the mouse button.
void mouseButton(int button, int state, int x, int y)
{
    if(button == GLUT_RIGHT_BUTTON) 
        exit(0);

    if(button == GLUT_LEFT_BUTTON) 
        switch(state) {
        case GLUT_DOWN:
            y = winHeight-y;
            startMotion(x, y);
            break;
        case GLUT_UP:
            y = winHeight-y;
            stopMotion(x, y);
            break;
        } 
}

// Spinning the objects - it's being called inside the applyRotation
// and can also be used as the iddle function.
void spinObject()
{
    if (redrawContinue) 
        glutPostRedisplay();
}
