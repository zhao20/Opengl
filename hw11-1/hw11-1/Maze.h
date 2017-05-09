/********************************************************************

 File:          Maze.h
 Author:        Dana Vrajitoru

 Description:   The class handling the maze.
 Project:       A sprite moving through a maze application.

 Last updated:  April 2017

 ********************************************************************/

#ifndef MAZE_H
#define MAZE_H

#include "Box.h"

const int mazew = 15, mazeh = 15;
const int mazeid = 2;

enum CellType {freeCl=0, wallCl, foodCl};

class Maze {
private:
	Box *brickBox, *foodBox, *floorBox; // help with drawing the maze

public:
	CellType table[mazew][mazeh];
	bool textureOn;

		// Default constructor. Should initialize the table.
	Maze();

		// destructor: delete the boxes
	~Maze();

		// load the 3 texture files
	void loadTextures();

		// Draws a single brick at given coordinates
	void drawCell(int x, int y);

		// Here is where we create the box objects and their display lists
	void init();

		// Calls the display lists assuming that the maze is drawn starting
		// from 0, 0.
	void display();
};

#endif
