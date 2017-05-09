//
//  Jupiter.c
//  hw7
//
//  Created by xingguo zhao on 5/1/17.
//  Copyright © 2017 xingguo zhao. All rights reserved.
//

#include "glheader.h"
#include "Jupiter.h"
#include <assert.h>
	// Constructor : initialize the default values and initialize the
	// display list for the Earth.
Jupiter::Jupiter()
		: Planet(0.7, 15, 8, 35)
{
		// redefine the color
	thisR = 0.3;
	thisG = 0.3;
	thisB = 1.0;

		// add the satellite
	nrChildren = 67;
	children = new CelestialPtr[nrChildren];

	for(int i = 0; i<nrChildren; i++){
		children[i] = new Planet( RandomFloat(0.01,0.1),
								 rand() %100+1,
								RandomFloat(0.2, 1),
								 rand()%360);
	}

}



float Jupiter::RandomFloat(float min, float max)
{
		// this  function assumes max > min, you may want
		// more robust error checking for a non-debug build
	assert(max > min);
	float random = ((float) rand()) / (float) RAND_MAX;

		// generate (in your case) a float between 0 and (4.5-.78)
		// then add .78, giving you a float between .78 and 4.5
	float range = max - min;
	return (random*range) + min;
}
