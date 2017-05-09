/********************************************************************
 File:          Player.h
 Author:        Dana Vrajitoru

 Description:   The class handling the player.
 Project:       A sprite moving through a maze application.

 Last updated:  February 10, 2017.
 ********************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "Maze.h"

class Player {
private:
		//Box *player;
public:
	Maze *world; // a reference to the board

	float posX, posY; // position on the board
	float width, height; // store the dimensions here

		// constructor
	Player();

		// initializes the display lists of components
	void draw();

		// displays the player on screen
	void display();

		// places the player at a given position on the board
	void teleport(float x, float y);

		// check for collision with the walls and other elements in the maze
		// return true if there is a collision that cannot be resolved by removing
		// the cell in the maze, such as for food
	bool checkCollision();

		// move the player horizontally, negative value for left, positive for right
		// this function should check for collision with the maze cells and if there
		// is collision with the walls, it should not make the move
	void moveHorizontal(float val);

		// move the player vertically, negative value for left, positive for right
		// this function should check for collision with the maze cells and if there
		// is collision with the walls, it should not make the move
	void moveVertical(float val);

	void loadTextures();
};

#endif
