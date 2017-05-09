/********************************************************************
  File:         Ball.cc
  Author:       Dana Vrajitoru
                
  Project:      A simple 2D animation program based on the Breakout game.
  Last updated: February 6, 2017.

  A class handling a 2D circle moving on the screen.

********************************************************************/

#include <cstdlib>
#include <cmath>
#include "glheader.h"
#include "Ball.h"
#include "stdio.h"

// Constructor with given boundaries for the window
Ball::Ball(float rad)
{
    x = y = 0;
    radius = rad;
    vx = vy = 1;
    r = 1;
    g = b = 0;
    bwidth = 1;
    bheight = 1;
    disk = gluNewQuadric();
}
//
//// Define the boundaries for the window
//void Ball::setBox(float bw, float bh)
//{
//    bwidth = bw;
//    bheight = bh;
//}
//
//// Set the color of the object
//void Ball::setColor(float valr, float valg, float valb)
//{
//    r = valr;
//    g = valg;
//    b = valb;
//}
//
//// Change its coordinates
//void Ball::jumpTo(float posx, float posy)
//{
//    x = posx;
//    y = posy;
//}

// Initialize the speed to some values.
void Ball::setSpeed(float tx, float ty)
{
    vx = tx;
    vy = ty;
}

// Reset the value of the speed with random values between 0 and the limit.
void Ball::randomizeSpeed(float limit)
{
    vx = limit * randUnit();
    vy = limit * randUnit();

}

// Move the ball from the current position based on its velocity. It
// also bounces the ball against the walls if it needs to.
void Ball::move()
{
    if (x+vx <0 || x+vx > bwidth)
        vx = -vx;
    x = x + vx;
    if (y+vy > bheight) // but if the ball hits the bottom border, it
        // falls off the window
        vy = -vy;
    y = y + vy;
}

// Draw the ball at given coordinates
void Ball::draw()
{
    gluQuadricDrawStyle(disk,(GLenum)GLU_FILL);
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x, y, 0); // we don't have the 3rd dimension yet
    gluDisk(disk, 0, radius, 10, 5);
    glPopMatrix();
}
