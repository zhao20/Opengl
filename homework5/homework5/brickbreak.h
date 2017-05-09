/********************************************************************
  File:         brickbreak.h
  Author:       Dana Vrajitoru
                
  Project:      A simple 2D animation program based on the Breakout game.
  Last updated: February 6, 2017.

  The interface of the program, keeping all the objects together and
  definisng their interaction.

********************************************************************/

#ifndef BRICKBREAK_H
#define BRICKBREAK_H


void createObjects();
// Draws all the objects in the scene
void draw();
//
//// Moves all the objects in the scene
//void move();

void key(unsigned char key, int x, int y);

void spkey(int key, int x, int y);

// Resets all the objects to their initial positions.
void resetObj();

// Application parameters
void myinit();

// Initialize the window and the GUI callbacks
void initWindowGui();

// To be called whenever the window is resized.
void myResize(int w, int h);

	//To check key press released
void upkey(int key, int x, int y);


void move(int value);

	// Checks if the game is over
bool gameOver();

	// Detects and resolves all the collisions
void resolveCollisions();
	// draw reamain lives on the left topo corner
void drawLifeBall();
#endif
