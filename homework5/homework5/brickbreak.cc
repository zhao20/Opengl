/********************************************************************
 File:         brickbreak.cc
 Author:       Dana Vrajitoru

 Project:      A simple 2D animation program based on the Breakout game.
 Last updated: February 6, 2017.

 The interface of the program, keeping all the objects together and
 definisng their interaction.

 ********************************************************************/

#include <cstdlib>
#include "glheader.h"
#include "Ball.h"
#include "brickbreak.h"
#include "Paddle.h"
#include <stdio.h>
#include "Brick.h"


int winWidth = 500, winHeight = 500;
int speed = 6;
int count = 0;		// this is a count for brick index
int remainLives = 4;	// total 4 balls: 1 regular and 3 extra
int nrObjects;
	//topSpareSpace which will leave the space on the top for displaying points or lives
	//brickSpareSpace whick will leave the a space on the left and right for the brick
float topSpareSpace = 5, brickSpareSpace = 1.5;


const float bwidth = 100, bheight = 100, rad = 2, w = 18, h=2;
const float brickWidth = 18, brickHeight = 3;
const int ROWS=3, COLS=5;


Ball theBall(rad);
Paddle thePaddle(w, h);		//initiallize paddle
GameObject **scene;
GameObject **lifeBall; 		//extra life balls



	// Draws all the objects in the scene
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i=0; i < nrObjects; i++){
		if (scene[i] && scene[i]->visible) // only draw visible objects
			scene[i]->draw();

	}
		//draw extra life balls
	drawLifeBall();
	glutSwapBuffers();
}

	//draw extra live balls on right top corner
void drawLifeBall(){
	for(int i=0;i<remainLives;i++){
			//check balls staill active
		if(lifeBall[i] && lifeBall[i]->visible){
			lifeBall[i]->draw();
				//set location for balls
			lifeBall[i]->jumpTo(bwidth-i*(2*rad+brickSpareSpace)-5, bheight-rad-0.5);
		}
	}
}
	//create Gameobects array
void createObjects()
{
	nrObjects = ROWS * COLS + 2; // bricks plus ball and paddle
	scene = new GameObjectPtr[nrObjects]; // allocate the memory
										  //initialize bricks
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS;j++){
				//pass x and y axis location and width and height to array
			scene[count] = new Brick(brickSpareSpace+j*(brickWidth+brickSpareSpace),
									 bheight-topSpareSpace-i*(brickHeight+brickSpareSpace),
									 brickWidth, brickHeight);
			count++;	//index
		}
	}
		//initialize extra life balls
	lifeBall = new GameObjectPtr[remainLives];
	for(int i=0;i<remainLives; i++){
			//initialize the ball with radius
		lifeBall[i] = new Ball(rad);
			//don't let balls move
		lifeBall[i]->active = false;
	}
	scene[ROWS * COLS] = &theBall; // register the ball in the array
	scene[ROWS * COLS + 1] = &thePaddle; //register the paddle in the array
}

	// Callback function for an Ascii key being pressed
void key(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q':
		case 'Q':
			exit(0);
		case '1':
			glutPostRedisplay();
			break;
		case ' ':		//space key
			if(theBall.y < -rad){	//check the ball out of panel
				resetObj();		//reset object
			}
			break;
	}
}

	// Callback function for a special key being pressed
void spkey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT:		//left arrow key
			speed+=2;		//continuelly increase speed
			thePaddle.moveLeft(speed);	//move the ball
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:		//right arrow key
			speed+=2;		//continuelly increase speed
			thePaddle.moveRight(speed);	//move the ball
			glutPostRedisplay();
			break;
	}
}

	// Initializes all the objects with their initial positions.
void resetObj()
{
	theBall.setBox(bwidth, bheight);
	theBall.jumpTo(bwidth/2, rad+h);
	theBall.randomizeSpeed(5);
	thePaddle.setBox(bwidth, bheight);
	thePaddle.jumpTo((bwidth-w)/2, 0);
	remainLives--;
	drawLifeBall();

}

	// Application parameters
void myinit()
{

	createObjects();
	resetObj();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, bwidth, 0, bheight);
	glMatrixMode(GL_MODELVIEW);
	glClearColor (0, 0, 0, 1.0);
	glColor3f(1.0,0.0,0.0);
		//glLineWidth(2);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
}

	// Initialize the window and the GUI callbacks
void initWindowGui()
{
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB );
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Breakout");
	glutDisplayFunc(draw);

	glutTimerFunc(50, move, 1);
	glutKeyboardFunc(key);
	glutSpecialFunc(spkey);
	glutSpecialUpFunc(upkey);	//spcial key release detect function
								//glutMouseFunc(mouse);
}

	// To be called whenever the window is resized.
void myResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
}

	//To check the key has been released
void upkey(int key, int x, int y){

	switch (key) {
				//the speed value will reset if key released
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			speed = 1;
			break;
	}
}

	// Moves all the objects in the scene
void move(int value)
{
	if (value) {
		for (int i=0; i < nrObjects; i++)
			if (scene[i] && scene[i]->active) // only move active objects
				scene[i]->move();
		resolveCollisions(); // detect and resolve collisions
		glutPostRedisplay();
		glutTimerFunc(50, move, !gameOver());
	}
}

	// Checks if the game is over
bool gameOver(){
		//reset index
	count = 0;
		//check any extra life exist
	if(remainLives<0) {
		theBall.visible = false;
		return true;
	}
		//check any bricks active
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS;j++){
				//still bricks exist, game contiue
			if(scene[count]->active){
				return false;
			}
			count++;
		}
	}
		//no more bircks exist, set ball invisible
	theBall.visible = false;
		//end the game
	return true;
}

	// Detects and resolves all the collisions
void resolveCollisions(){


	if (theBall.y < -rad){
		glutIdleFunc(NULL);
	}else if(thePaddle.intersect(theBall)){
		theBall.vy *= -1;		//reverse moving direction
								//theBall.vx *= -1;		//reverse moving direction

	}

	count = 0; 		//reset index
	//check collisions with the ball
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS;j++){
			if( scene[count]->intersect(theBall)){
					//set brick invisible
				scene[count]->visible = false;
					//set brick inactive
				scene[count]->active = false;
				theBall.vy *= -1;		//reverse moving direction
				//theBall.vx *= -1;		//reverse moving direction
				break;
			}
			count++;
		}
	}

	glutPostRedisplay();

}

