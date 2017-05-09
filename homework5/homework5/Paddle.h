/********************************************************************
  File:         Paddle.h
  Author:       Dana Vrajitoru
                
  Project:      A simple 2D animation program based on the Breakout game.
  Last updated: February 9, 2017.

  A class handling the paddle that catches the ball.

********************************************************************/

#ifndef PADDLE_H
#define PADDLE_H

#include "Ball.h"

class Paddle: public GameObject {
public:

    // How big the paddle is
    float width, height;

    // default constructor with given 
    Paddle(float w=4, float h=1);

    // Move the paddle left and right. If the paddle goes out of the
    // window, don't move. These should be called from the arrow keys.
    void moveLeft(float tx);
    void moveRight(float tx);

    // Draw the paddle at given coordinates
    virtual void draw();

    // Function to figure out if the paddle and the ball intersect
    virtual bool intersect(Ball &b);
};

#endif
