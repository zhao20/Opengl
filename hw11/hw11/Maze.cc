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
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

const float pad = 0.1;

// Default constructor. Should initialize the table.
Maze::Maze()
    : brickBox(NULL), foodBox(NULL), floorBox(NULL), textureOn(false)
{

    int i, j;

	srand(time(NULL)); // randomize seed

		//static int tab[mazew][mazeh];
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
//
//	   {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//		{1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
//		{1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
//		{1, 0, 1, 1, 1, 0, 0, 2, 0, 1, 2, 1, 1, 0, 1},
//		{1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1},
//		{1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 2, 1, 1, 0, 1},
//		{1, 0, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 1},
//		{1, 0, 0, 0, 0, 2, 1, 0, 0, 1, 0, 1, 1, 0, 1},
//		{1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
//		{1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
//		{1, 0, 0, 0, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//		{1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
//		{1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
//		{1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1},
//		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

		//initialize the maze array
	for(i=0;i<mazew; i++){
		for(j=0;j<mazeh;j++){
			if(i == 0 || j==0){
				tab[i][j] = wallCl;
			}else if(i== (mazew-1) || j == (mazeh-1)){
				tab[i][j] = wallCl;
			}else{
				tab[i][j] = freeCl;
			}
			path[i][j] = 0;
		}
	}
		//generate random maze
	mazeGenerate(1,1, mazeh-2,mazew-2);
		//check and fix maze
	mazeCheck();

		//apply to matix to maze
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

	//this function will
void Maze::mazeGenerate(int x, int y, int height, int width){
 int randX, randY;


	if (height <= 2 || width <= 2)
		return;

		//horizental
	randX=x+rand()%(height/2)*2+1;
	for (int i = y; i < y + width; i++) {
		tab[randX][i] = wallCl;
	}

		//vertical
	randY=y+rand()%(width/2)*2+1;
	for (int i = x; i < x + height; i++) {
		tab[i][randY] = wallCl;
	}

		//directions
	int dig = rand()%4;
	switch (dig)
	{
		case 0:
			//dig three hole on the wall
		reverse(randX + 1, randY, x + height - 1, randY);// 1
		reverse(randX, randY + 1, randX, y + width - 1);// 2
		reverse(x, randY, randX - 1, randY);// 3
		break;
		case 1:
		reverse(randX, randY + 1, randX, y + width - 1);// 2
		reverse(x, randY, randX - 1, randY);// 3
		reverse(randX, y, randX, randY - 1);// 0
		break;
		case 2:
		reverse(x, randY, randX - 1, randY);// 3
		reverse(randX, y, randX, randY - 1);// 0
		reverse(randX + 1, randY, x + height - 1, randY);// 1
		break;
		case 3:
		reverse(randX, y, randX, randY - 1);// 0
		reverse(randX + 1, randY, x + height - 1, randY);// 1
		reverse(randX, randY + 1, randX, y + width - 1);// 2
		break;
		default:
		break;
	}

		// left down
	mazeGenerate(randX + 1, y, height - randX + x - 1, randY - y);
		// left up
	mazeGenerate(x, y, randX - x, randY - y);
		// right up
	mazeGenerate(x, randY + 1, randX - x, width - randY + y - 1);
		// right down
	mazeGenerate(randX + 1, randY + 1, height - randX + x - 1, width - randY + y - 1);

}

	/*
	 	check the special coditions in the maze like not path to start point. 
	 	or too many walls.
	 */
void Maze::mazeCheck(){
	int space  = 0;	//not wall space
	int wall = 0;	//walls
	//this loop will travesal whole array to check special case
	for( int i = 1; i<mazew-1;i++){
		for(int j = 1; j<mazeh-1; j++){
			if (isCorner(i,j) || isEdge(i,j))
				continue;
			wall = 0;
			space = 0;
				//check amount of walls
			if(tab[i][j] == wallCl){
				tab[i-1][j-1]==wallCl?wall++:space++;
				tab[i-1][j]==wallCl?wall++:space++;
				tab[i-1][j+1]==wallCl?wall++:space++;
				tab[i][j-1]==wallCl?wall++:space++;
				tab[i][j+1]==wallCl?wall++:space++;
				tab[i+1][j-1]==wallCl?wall++:space++;
				tab[i+1][j]==wallCl?wall++:space++;
				tab[i+1][j+1]==wallCl?wall++:space++;
				if(wall >=5)		//too may walls
					tab[i][j] = freeCl;	//make it
			}
		}

	}

}
	//check corner
bool Maze::isCorner(int x, int y){
		//only four corners
	if((x==1 && y==1) || (x== mazew-2 && y==1)
	   	||(x==1 && y==mazeh-2) || (x==mazew-2 && y==mazeh-2))
		return true;
	return false;
}

	//check edge of the maze
bool Maze::isEdge(int x, int y){
	if(x==0 || x==mazew-1||y==0 || y==mazeh-1)
			return true;
	return false;
}
	//check current space to start point
	//if there is route to start point return true
	//this function is not working properly
bool Maze::pathFinding(int x, int y){

		//start point
	if(x == 7 && y==1){
		return true;
	}
		//increasing weight for find path
	path[x][y]++;
		//each number is a direction, total is 4 which mean 4 direction has been checked.
	if (path[x][y] == 4 || (path[x][y] == 3 && isEdge(x, y)) ||(isCorner(x,y) && path[x][y])){
		return false;
			//hit wall to return
	}else if(tab[x][y] == wallCl)
		return false;
		//four directions checking
	if(pathFinding(x+1, y))
	   return true;
	if(pathFinding(x-1, y))
	   return true;
	if(pathFinding(x, y-1))
	   return true;
	if(pathFinding(x, y+1))
	   return true;

	return false;
}

	//random revert a wall to be free space or food
void Maze::reverse(int x1, int y1, int x2, int y2) {
	int random;
		//only dig whole when it inside range
		//to limit number of holes
	if (x1 == x2) {
		random = y1 + rand()%((y2 - y1 )/2+ 1)*2;//在奇数位置开门
		if(rand()%2 ==0)
			tab[x1][random] = freeCl;
		else
			tab[x1][random] = foodCl;
	}
		//same as above
 	if (y1 == y2) {
		random = y1 + rand()%((y2 - y1 )/2+ 1)*2;//在奇数位置开门
		if(rand()%2 == 0)
			tab[random][y1] = freeCl;
		else
			tab[random][y1] = foodCl;
	}


}

	//count number of spaces around current position
int Maze::spaceCount(int x, int y){
	int spaceCount = 0;
	if (tab[x-1][y]==freeCl)
		spaceCount++;
	if (tab[x+1][y]==freeCl)
		spaceCount++;
	if (tab[x][y+1]==freeCl)
		spaceCount++;
	if (tab[x][y-1]==freeCl)
		spaceCount++;
	if(spaceCount<3)
		printf("%d , %d , Spece %d\n", x, y, spaceCount);
	return spaceCount;

}
