	//
	//  Brick.hpp
	//  homework5
	//
	//  Created by xingguo zhao on 2/16/17.


#include <cstdlib>
#include <cmath>
#include "glheader.h"
#include <stdio.h>
#include "Brick.h"

	//Constractor to intialize all the values
Brick::Brick(float posX, float posY, float w, float h):GameObject(){

	x = posX;
	y = posY;
	width = w;
	height = h;
	r = 1.0;
	g = 1.0;
	b = 1.0;
	bwidth =1 ;
	bheight = 1;
}

void Brick::draw(){
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
	glVertex2f( x, y );		//left top
	glVertex2f( x+width, y );		//right top
	glVertex2f( x+width, y-height);	//right bottom
	glVertex2f( x,y-height);		//left bootom
	glVertex2f(x, y);			//left top
	glEnd( );

}
	//Check ball intersection between ball and Brick
bool Brick::intersect(Ball &b){
		if(!active) return false;
		//check the ball is in the range of Brick's coordinates
	if(b.y+b.radius > y-height && b.x+b.radius>=x && b.x-b.radius<x+width){

		return true;
	}

	return false;
	
}
