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
#include "interface.h"




	// constructor
Player::Player()
{

	width = 0.5;		//width of the player box
	height = 0.5;		//height of the player box
	player = new Box(width,height ,width);	//initilize player
}

	// initializes the display lists of components
void Player::draw()
{
		// load the textures
	loadBitmap("tan.bmp", player->texture,
			   player->widthT, player->heightT);
		//make texture for player
	makeTexture(player->texture, player->widthT, player->heightT);
	player->display();	//display player box
	player->drawTexture();	//applyer texture on player
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
		//print out curren position for player
	printf("posX : %f  +  posY: %f\n", posX, posY);

		//right
	if(world->table[(int)(posX+width)][(int)posY] ==1)
		return true;
		//left
	if(world->table[(int)(posX)][(int)posY] ==1)
		return true;
		//up
	if(world->table[(int)posX][(int)(posY+width)] ==1)
		return true;
		//down
	if(world->table[(int)posX][(int)posY] ==1)
		return true;

	return false;
}

	// move the player horizontally, negative value for left, positive for right
	// this function should check for collision with the maze cells and if there
	// is collision with the walls, it should not make the move
void Player::moveHorizontal(float val)
{
	posX += val;
		//check collision of food
	if(world->table[(int)posX][(int)posY] ==2){
		world->table[(int)posX][(int)posY] = freeCl;
		height += 0.2;	//increase height of player
		//apply new size for player box
		player = new Box(width, height, width);
	}
	else if (checkCollision()) // are we running into a wall?
		posX -= val; // go back
	display();	//refresh player

}

	// move the player vertically, negative value for left, positive for right
	// this function should check for collision with the maze cells and if there
	// is collision with the walls, it should not make the move
void Player::moveVertical(float val)
{
	posY += val;
		//check collision of food
	if(world->table[(int)posX][(int)posY] ==2){
		world->table[(int)posX][(int)posY] = freeCl;
		height += 0.2;	//increase height for player
		//apply new size for player
		player = new Box(width, height, width);
	}
	else if (checkCollision()) // are we running into a wall?
		posY -= val; // go back
	display();	//refresh player
}
