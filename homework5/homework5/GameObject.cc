/********************************************************************
  File:         GameObject.cc
  Author:       Dana Vrajitoru
                
  Project:      A simple 2D animation program based on the Breakout game.
  Last updated: February 9, 2017.

  A class providing a generic game object for all the others to
  inherit from.

********************************************************************/

#include "GameObject.h"

// default constructor
GameObject::GameObject()
    : visible(true), active(true)
{
    // setup some default values
    jumpTo(0, 0);
    setBox(0, 0);
    setColor(1, 1, 1); // white
}

// Define the boundaries for the window
void GameObject::setBox(float bw, float bh)
{
    bwidth = bw;
    bheight = bh;
}

// Set the color of the object
void GameObject::setColor(float valr, float valg, float valb)
{
    r = valr;
    g = valg;
    b = valb;
}

// Change its coordinates
void GameObject::jumpTo(float posx, float posy)
{
    x = posx;
    y = posy;
}

// Draw the object. To be implemented in derived classes.
void GameObject::draw()
{
    ; // nothing to do here
}

// Move the object. To be implemented in derived classes.
void GameObject::move()
{
    ; // nothing to do here
}

// Function to figure out if the object and the ball intersect
bool GameObject::intersect(Ball &b)
{
    return false;
}


