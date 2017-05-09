/*************************************************************************
 FILE:   surface.cc
 Functions used to generate curves and surfaces.

 Author: Dana Vrajitoru, IUSB
 Class:  C481 B581 Computer Graphics

 Modification: Xingguo Zhao
 Description: This class provdes function to do normalization, computation of
 Rotate pointf on Y axis and draw a surface.
 **************************************************************************/

#include <cmath>
#include "Point3f.h"

	// Builds a circle in the xy plane with given center and radius made
	// of 20 points. The first point is repeated a the end to create a
	// loop. It stores the points and normals in the last two
	// parameters. This is supposed to be drawn as a line strip.
void circleXy(float centerx, float centery, float centerz, float radius,
			  vector3f &points, vector3f &normals)
{
	Point3f p, n;
	p[2] = centerz;
	n[2] = 0;
	const int nrPoints = 20;
	float angle =0, delta_angle = 2*M_PI/nrPoints;
	for (int i=0; i<=nrPoints; i++) {
		angle += delta_angle;
			// The normal in the point : we want it to be a unit vector.
		n[0] = cos(angle);
		n[1] = sin(angle);
			// We can use the normat to compute the point itself.
		p[0] = centerx +radius * cos(angle);
		p[1] = centery +radius * sin(angle);
			// Add these to the points and normals.
		points.push_back(p);
		normals.push_back(n);
	}
}

	// Draws a curve as a line strip; we have no use for the normals for a
	// line strip.
void drawLineStrip(vector3f &points)
{
	glBegin(GL_LINE_STRIP);
	for (int i=0; i<points.size(); i++)
		points[i].glVertex();
	glEnd();
}

	// Compute the normals for a curve in the xy plane. You can use the
	// function orthogonalXy from the Point3f class. For each 2 line
	// segments in a sequence, the normal should be the average of the two
	// normals computed on each segment. If the first and last point are
	// the same, then the normal in the first and last points should be
void computeNormalsXy(vector3f &points, vector3f &normals)
{
		//temporary values
	Point3f n, v, next, nr, nResult;
		//check the there more than one point
	if(points.size() >1)
		{
			//traversal all the points
		for(int i=0; i<points.size();i++)
			{
				//first point
			if(i==0)
				{
					//p2-p1
				v[0] = points[i+1][0]-points[i][0];
				v[1] = points[i+1][1]-points[i][1];
				v[2] = points[i+1][2]-points[i][2];
					//last point loop back to first point
				if(points[i] == points[points.size()-1])
					{
					int pSize = points.size();
						//last point - first point
					next[0] = points[0][0]-points[pSize-1][0];
					next[1] = points[0][1]-points[pSize-1][1];
					next[2] = points[0][2]-points[pSize-1][2];
						//normalize vector
					n.orthogonalXy(v);
					nr.orthogonalXy(next);
						//get the average after normalization
					nResult[0] = (n[0] +nr[0]) * 0.5;
					nResult[1] = (n[1] +nr[1]) * 0.5;
					nResult[2] = (n[2] +nr[2]) * 0.5;
					}
				else
					{
						//not loop back to start point
					nResult.orthogonalXy(v);
					}
					//last point check
				}
			else if(i==points.size()-1)
				{
					//last point subtract previus point
				v[0] = points[i][0]-points[i-1][0];
				v[1] = points[i][1]-points[i-1][1];
				v[2] = points[i][2]-points[i-1][2];
					//check last point loop back to first point
				if(points[i] == points[0] )
					{
						//last point - first point
					next[0] = points[i][0]-points[0][0];
					next[1] = points[i][1]-points[0][1];
					next[2] = points[i][2]-points[0][2];
						//norlize vectors
					n.orthogonalXy(v);
					nr.orthogonalXy(next);
						//get average vector after normalization
					nResult[0] = (n[0] +nr[0]) * 0.5;
					nResult[1] = (n[1] +nr[1]) * 0.5;
					nResult[2] = (n[2] +nr[2]) * 0.5;
					}
				else
					{
						//not loop back to start
					nResult.orthogonalXy(v);
					}
				}
			else
				{
				v[0] = points[i][0]-points[i-1][0];
				v[1] = points[i][1]-points[i-1][1];
				v[2] = points[i][2]-points[i-1][2];
					//v = points[i]-=points[i-1];
				next[0] = points[i+1][0]-points[i][0];
				next[1] = points[i+1][1]-points[i][1];
				next[2] = points[i+1][2]-points[i][2];
					//next = points[i+1] -=points[i];
				n.orthogonalXy(v);
				nr.orthogonalXy(next);
				nResult[0] = (n[0] +nr[0]) * 0.5;
				nResult[1] = (n[1] +nr[1]) * 0.5;
				nResult[2] = (n[2] +nr[2]) * 0.5;
					//n=(n+=nr)*=0.5;
				}
			normals.push_back(nResult);
			}

		}

}

	// Given a curve with normals in the xy plane, the function builds a
	// rotation surface by rotating this curve around the Oy axis. It also
	// computes the normals to the surface given the normals to the curve.
void rotationSurfaceY(vector3f &curvePt, vector3f &curveNm,
					  matrix3f &surfacePt, matrix3f &surfaceNm)
{
		//temporary value to hold points
	Point3f p, n;
		//number of parts going to divide a circle
	const int nrPoints = 20;
	float angle = 0, delta_angle = 2 * M_PI / nrPoints;
		//rotate vectors
	for (int i = 0; i <= nrPoints; i++)
		{
			//temporary vector to store the rotated points
		vector3f pt, nm;
			//increase angle after each transform
		angle += delta_angle;
			//rotate every points inside of vector
		for (int j = 0; j < curvePt.size(); j++)
			{
				//x
			p[0] = curvePt[j][0] * cos(angle);
				//y
			p[1] = curvePt[j][1];
				//z
			p[2] = curvePt[j][0] * sin(angle);
				//x
			n[0] = curveNm[j][0] * cos(angle);
				//y
			n[1] = curveNm[j][1];
				//z
			n[2] = curveNm[j][0] * sin(angle);
				//store points after transform
			pt.push_back(p);
			nm.push_back(n);
			}
			//store vectors to matrix
		surfaceNm.push_back(nm);
		surfacePt.push_back(pt);
		}

}

	// Draws the surface given as a grid of points as a sequence of
	// triangle strips.
void drawSurface(matrix3f &surfacePt, matrix3f &surfaceNm)
{
		//traversal points inside of maxtrices
	for (int i = 0; i < (surfacePt.size() - 1); i++)
		{
		glBegin(GL_TRIANGLE_STRIP);
			//draw surface
		for (int j = 0; j < surfacePt[i].size(); j++)
			{
			surfaceNm[i][j].glNormal();
			surfacePt[i][j].glVertex();
			surfaceNm[i+1][j].glNormal();
			surfacePt[i+1][j].glVertex();
			}
		glEnd();
		
		}
	
}
