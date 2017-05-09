/********************************************************************
  File:         illusion.cc
  Author:       Dana Vrajitoru
  Project:      Optical illusion
  Last updated: January 23, 2017.

  Functions creating the content of the window

********************************************************************/

#include "glheader.h"
#include "illusion.h"
#include <cstdlib>
#include <iostream>
using namespace std;
//void horizontalLine(float gap, float width, float height);

// display an optical illusion that creates a lens effect by drawing
// lines from the sides of the window towards the center at increasing
// distances from each other
void lensIllusion(float gap, float color[], float width, float height)
{
    int current = gap, count = 0;
    int i, j;

    glColor3f(color[0], color[1], color[2]);
 	glBegin(GL_LINES);

	/***************** Horizontal Line*********************/
    i=1;
    while (current < height/2 ){
		glVertex2f(0, current);		//button left
		glVertex2f(width, current);	//button right
		glVertex2f(0, height -current);	//top left
		glVertex2f(width, height-current);	//top right
		i++;
		current +=i*gap;	// go to next position
	}

	/********************* Vertical line *******************/
	current = gap;	//reset current value to gap value which is 5 for default
	j=1;
	while(current < width/2){
		glVertex2f(current, 0);		//top left
		glVertex2f(current, height);		//button left
		glVertex2f(width - current, 0);		//top right
		glVertex2f(width - current , height);		//button right
		j++;
		current += j*gap;
	}
	glEnd();
}


