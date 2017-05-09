/********************************************************************
 File:         sierpinski.cc
 Author:       Dana Vrajitoru
 Based on the example provided in
 E. Angel, Interactive Computer Graphics.
 Project:      An implementation of the Sierpinski gasket.
 Last updated: January 30, 2017.

 Drawing a fractal using triangles.

 ********************************************************************/

#include "glheader.h"
#include "interface.h"
#include "sierpinski.h"
#include "stdio.h"


	// display one triangle
void triangle( Point2 a, Point2 b, Point2 c)
{
	glBegin(GL_TRIANGLES);
	glVertex2fv(a);
	glVertex2fv(b);
	glVertex2fv(c);
	glEnd();
}

	// Implementation of the Sierpinski gasket by triangle subdivision
	// using vertex numbers.
void divide_triangle(Point2 a, Point2 b, Point2 c, int m)
{
	Point2 v0, v1, v2;
	int j;
	if (m>0) {
		for(j=0; j<2; j++)
			v0[j]=(a[j]+b[j])/2;
		for(j=0; j<2; j++)
			v1[j]=(a[j]+c[j])/2;
		for(j=0; j<2; j++)
			v2[j]=(b[j]+c[j])/2;
		divide_triangle(a, v0, v1, m-1);
		divide_triangle(c, v1, v2, m-1);
		divide_triangle(b, v2, v0, m-1);
	}
	else
		triangle(a,b,c); // draw triangle at end of recursion
}



/*
 Square position:
 7 8 9
 4 5 6
 1 2 3
 */
	// Implementation of the Sierpinski "carpet".
void carpet(Point2 start, float width, int m)
{
	if(m== 0){
			//This part will draw a square bese on the width
		glBegin(GL_POLYGON);
		glVertex2fv(start);
		glVertex2f(start[0], start[1]+width);
		glVertex2f(start[0]+width, start[1]+width);
		glVertex2f(start[0]+width, start[1]);
		glVertex2f(start[0], start[1]);

		glEnd();
	}
	else{
		float interval = width /3;
		Point2 currentStart = {start[0], start[1]};

			//printf("interval : %f of width %f \n" , interval, width);
		carpet(currentStart, interval, m-1); 		//position 1
		currentStart[0] += interval;
		carpet(currentStart, interval, m-1);		//position 2

		currentStart[0] += interval;
		carpet(currentStart, interval, m-1);		//position 3

		currentStart[0] = start[0];
		currentStart[1] += interval;
		carpet(currentStart, interval, m-1);		//position 4

		currentStart[0] += interval;					//skip position 5
			//carpet(currentStart, interval, m-1);		//position 5

		currentStart[0] += interval;
		carpet(currentStart, interval, m-1); 		//position 6

		currentStart[0] = start[0];
		currentStart[1] += interval;
		carpet(currentStart, interval, m-1);		//position 7

		currentStart[0] += interval;
		carpet(currentStart, interval, m-1);		//position 8

		currentStart[0] += interval;
		carpet(currentStart, interval, m-1);		//position 9
		
	}
	
}

