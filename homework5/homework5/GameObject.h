/********************************************************************
  File:         GameObject.h
  Author:       Dana Vrajitoru
                
  Project:      A simple 2D animation program based on the Breakout game.
  Last updated: February 6, 2017.

  A class providing a generic game object for all the others to
  inherit from.

********************************************************************/

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <cstdlib>

class Ball;

inline float randUnit()
{   
    return float(abs(rand()))/RAND_MAX;
}

class GameObject {
public:    
    // The object's position
    float x, y;
    // Color of the object
    float r, g, b;
    // Bounding box of the play area
    float bwidth, bheight;
    // Game attributes
    bool visible, active;

    // default constructor
    GameObject();

    // Define the boundaries for the play area
    void setBox(float bw, float bh);
    // Set the color of the object
    void setColor(float valr, float valg, float valb);

    // Change its coordinates
    void jumpTo(float posx, float posy);

    // Draw the object. To be implemented in derived classes.
    virtual void draw();
    // Move the object. To be implemented in derived classes.
    virtual void move();

    // Function to figure out if the object and the ball intersect
    virtual bool intersect(Ball &b);
};

typedef GameObject *GameObjectPtr;

#endif
