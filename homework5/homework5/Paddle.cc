//
//  Paddle.cpp
//  hw4
//
//  Created by xingguo zhao on 2/7/17.
//
//	This class file is about drawing, moving and other reaction with paddle.


#include <cstdlib>
#include <cmath>
#include "glheader.h"
#include <stdio.h>
#include "Paddle.h"

	//Constractor to intialize all the values
Paddle::Paddle(float w, float h){

	x = 0;
	y = 0;
	width = w;
	height = h;
	r = 1.0;
	g = 1.0;
	b = 1.0;
	bwidth =1 ;
	bheight = 1;
}

	//Move paddle to left
void Paddle::moveLeft(float tx){
		//check x is not negative
	if(x-tx>0){
		x -= tx;
	}else{
		x = 0;	//limit paddle inside boundry
	}
}

	//Move paddle to right
void Paddle::moveRight(float tx){
		//check paddle is not out of range
	if(x+tx <bwidth-width)
		{x += tx;
		}else {
				//set paddle to limit boundry
			x = bwidth-width;
		}
}
	//Draw paddle by given values
void Paddle::draw(){
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
	glVertex2f( x, y );		//left bottom
	glVertex2f( x+width, y );		//right bottom
	glVertex2f( x+width, y+height);	//right top
	glVertex2f( x,y+height);		//legt top
	glVertex2f(x, y);			//left bottom
	glEnd( );

}
	//Check ball intersection between ball and paddle
bool Paddle::intersect(Ball &b){
		//check the ball is in the range of paddle's coordinates
	if(b.y-b.radius < y+height && b.x+b.radius>=x && b.x-b.radius<x+width){
		return true;
	}
	return false;

}



