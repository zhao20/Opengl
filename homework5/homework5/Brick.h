//
//  Brick.hpp
//  homework5
//
//  Created by xingguo zhao on 2/16/17.
//

#ifndef Brick_hpp
#define Brick_hpp

#include <stdio.h>

#include "Ball.h"

class Brick: public GameObject {
public:

		// How big the Brick is
	float width, height;

		// default constructor with given
	Brick(float posX, float posY, float h, float w);


		// Draw the Brick at given coordinates
	virtual void draw();

		// Function to figure out if the Brick and the ball intersect
	virtual bool intersect(Ball &b);
};



#endif /* Brick_hpp */
