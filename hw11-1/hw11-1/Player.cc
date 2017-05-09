/********************************************************************
 File:          Player.cc
 Author:        Dana Vrajitoru

 Description:   The class handling the player.
 Project:       A sprite moving through a maze application.

 Last updated:  February 10, 2017.
 ********************************************************************/

#include "glheader.h"
#include "Player.h"
#include "time.h"
#include "stdio.h"
#include "bitmap.h"




	// constructor
Player::Player()
{
	posX = 0;
	posY = 0;
	width = 0.4;
		//player = new Box(width,width ,width);
}

	// initializes the display lists of components
void Player::draw()
{
		// assume that you draw the object at position 0 here
		//glTranslatef(0, 0, 0.5);
	glColor3f(1, 1, 1);
		//	player->draw();
		//	player->drawTexture();
		//glutSolidCube(width);
		//glutSolidSphere (.3, 50, 50);
}

	// displays the player on screen
void Player::display()
{
	glPushMatrix();
	glTranslatef(posX, 0, posY);

		// whatever else you are drawing
	draw();
	glPopMatrix();
}

	// places the player at a given position on the board
void Player::teleport(float x, float y)
{
	posX = x;
	posY = y;
}

	// check for collision with the walls and other elements in the maze
	// return true if there is a collision that cannot be resolved by removing
	// the cell in the maze, such as for food
bool Player::checkCollision()
{

	printf("posX : %f  +  posY: %f\n", posX, posY);

		//right
	if(world->table[(int)(posX+width)][(int)posY])
		return true;
		//left
	if(world->table[(int)(posX)][(int)posY] )
		return true;
		//up
	if(world->table[(int)posX][(int)(posY+width)])
		return true;

	if(world->table[(int)posX][(int)posY])
		return true;

		//
		//	int upX = (int)(posX + width/2);
		//	int upY = (int)(posY -width/2);
		//	int	downX = (int)(posX - width/2);
		//	int downY = (int)(posY +width/2);
		//		//north
		//	if(world->table[(int)posX][upY] == 1)
		//		return true;
		//		//east
		//	if(world->table[downX][(int)posY] == 1)
		//		return true;
		//		//south
		//	if(world->table[(int)posX][downY] == 1)
		//		return true;
		//		//west
		//	if(world->table[upX][(int)posY] == 1)
		//		return true;

		//	if(world->table[(int)(posX-width)][(int)(posY+width)])
		//		return true;
	return false;
}

	// move the player horizontally, negative value for left, positive for right
	// this function should check for collision with the maze cells and if there
	// is collision with the walls, it should not make the move
void Player::moveHorizontal(float val)
{
	posX += val;
	if (checkCollision()) // are we running into a wall?
		posX -= val; // go back
}

	// move the player vertically, negative value for left, positive for right
	// this function should check for collision with the maze cells and if there
	// is collision with the walls, it should not make the move
void Player::moveVertical(float val)
{
	posY += val;
	if (checkCollision()) // are we running into a wall?
		posY -= val; // go back
}

	//	// load the 3 texture files
	//void Player::loadTextures()
	//{
	//		// load the textures
	//	loadBitmap("flower.bmp", player->texture,
	//			   player->widthT, player->heightT);
	//
	//
	//}
