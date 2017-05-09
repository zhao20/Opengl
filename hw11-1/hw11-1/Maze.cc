/********************************************************************
 File:          maze.cc
 Author:        Dana Vrajitoru

 Description:   The class handling the maze.
 Project:       A sprite moving through a maze application.

 Last updated:  February 10, 2017.
 ********************************************************************/

#include "glheader.h"
#include <cstdlib>
#include "Maze.h"
#include "bitmap.h"
#include "interface.h"

const float pad = 0.1;

	// Default constructor. Should initialize the table.
Maze::Maze()
: brickBox(NULL), foodBox(NULL), floorBox(NULL), textureOn(false)
{
	int i, j;
	static int tab[mazew][mazeh] =
		//        {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		//         {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		//         {1, 1, 0, 1, 1, 0, 1, 0, 1, 1},
		//         {1, 0, 0, 2, 1, 0, 2, 0, 0, 1},
		//         {1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
		//         {1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
		//         {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		//         {1, 1, 1, 2, 1, 0, 1, 2, 1, 1},
		//         {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		//         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 0, 2, 0, 1, 2, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 2, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 2, 1, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 0, 0, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


	for (i=0; i<mazew; i++)
		for (j=0; j<mazeh; j++)
			table[i][j] = CellType(tab[i][j]);
}

	// destructor: delete the boxes
Maze::~Maze()
{
	if (brickBox)
		delete brickBox;
	if (foodBox)
		delete foodBox;
	if (floorBox)
		delete floorBox;
}

	// Draws a cell at given coordinates
void Maze::drawCell(int x, int y)
{
	switch (table[x][y]) {
		case wallCl:
			if (!textureOn)
				glColor3f(0.5, 0.35, 0.25); // dark brown
			else
				makeTexture(brickBox->texture, brickBox->widthT, brickBox->heightT);
			glPushMatrix();
			glTranslatef(float(x) + pad, 0, y + pad);
			brickBox->display();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);// other cells may not use this texture
			break;
		case foodCl:
			if (!textureOn)
				glColor3f(1.0, 0.3, 0.1); // red-orange
			else
				makeTexture(foodBox->texture, foodBox->widthT, foodBox->heightT);
			glPushMatrix();
			glTranslatef(x + 0.25, 0, y + 0.25);
			foodBox->display();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);// other elements may not use this texture
			break;
	}
}

	// Here is where we create the display lists
void Maze::init()
{
	int i, j;
		// set the dimensions for the elements
	brickBox = new Box(1.0-pad/2, 1.0-pad/2, 1.0-pad/2); // with a bit of space
	foodBox = new Box(0.5, 0.5, 0.5);
	floorBox = new Box(mazew + 2*pad, pad, mazeh + 2*pad);
	floorBox->setTiling(mazew, mazeh);
		// ^ with a small border around the maze

		// create the display lists
	brickBox->drawTexture();
	foodBox->drawTexture();
	floorBox->drawTexture();
}

	// Calls the display lists assuming that the maze is drawn starting
	// from 0, 0.
void Maze::display()
{
		// draw the floor first
	if (!textureOn)
		glColor3f(0.8, 0.65, 0.55); // light brown
	else
		makeTexture(floorBox->texture, floorBox->widthT, floorBox->heightT);
	glPushMatrix();
	glTranslatef(-pad, -pad, -pad);
	floorBox->display();
	glPopMatrix();

		// then all the maze elements
	for (int i=0; i<mazew; i++)
		for (int j=0; j<mazeh; j++)
			drawCell(i, j);
}

	// load the 3 texture files
void Maze::loadTextures()
{
		// load the textures
	loadBitmap("pattern.bmp", floorBox->texture,
			   floorBox->widthT, floorBox->heightT);
	loadBitmap("marble.bmp", foodBox->texture,
			   foodBox->widthT, foodBox->heightT);
	loadBitmap("tiles.bmp", brickBox->texture,
			   brickBox->widthT, brickBox->heightT);

}
