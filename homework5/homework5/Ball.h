/********************************************************************
  File:         Ball.h
  Author:       Dana Vrajitoru
                
  Project:      A simple 2D animation program based on the Breakout game.
  Last updated: February 9, 2017.

  A class handling a 2D circle moving on the screen.

********************************************************************/

#ifndef BALL_H
#define BALL_H

#include "GameObject.h"

class Ball: public GameObject {
public:
    // How big the ball is
    float radius;
    // Velocity over x and y
    float vx, vy;

    GLUquadric *disk;

    // default constructor with given 
    Ball(float rad = 1.0);

    // Initialize the speed to some values.
    void setSpeed(float tx, float ty);
    // Reset the value of the speed with random values between 0 and the limit.
    void randomizeSpeed(float limit);

    // Move the ball from the current position based on its velocity
    virtual void move();
    // Draw the ball at given coordinates
    virtual void draw();
};

#endif
