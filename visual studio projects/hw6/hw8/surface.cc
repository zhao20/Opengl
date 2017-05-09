/*************************************************************************
FILE:   surface.cc
Functions used to generate curves and surfaces.

Author: Dana Vrajitoru, IUSB
Class:  C481 B581 Computer Graphics
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
	const int nrPoints = 120;
	float angle = 0, delta_angle = 2 * M_PI / nrPoints;
	for (int i = 0; i <= nrPoints; i++) {
		angle += delta_angle;
		// The normal in the point : we want it to be a unit vector.
		n[0] = cos(angle);
		n[1] = sin(angle);
		// We can use the normat to compute the point itself.
		p[0] = centerx + radius * cos(angle);
		p[1] = centery + radius * sin(angle);
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
	for (int i = 0; i < points.size(); i++)
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
	Point3f n;

	for (int i = 0; i < points.size(); i++) {
		if (i == 0) {
			n.orthogonalXy(points[i]);
		}
		else if (i == points.size() - 1) {
			n.orthogonalXy(points[i]);
		}
		else {
			n.orthogonalXy((points[i] += points[i - 1]) *= 0.5);
		}
		normals.push_back(n);
	}

}

// Given a curve with normals in the xy plane, the function builds a
// rotation surface by rotating this curve around the Oy axis. It also
// computes the normals to the surface given the normals to the curve.
void rotationSurfaceY(vector3f &curvePt, vector3f &curveNm,
	matrix3f &surfacePt, matrix3f &surfaceNm)
{
	Point3f p, n;
	vector3f pt, nm;
	const int nrPoints = 120;
	float angle = 0, delta_angle = 2 * M_PI / nrPoints;

	for (int i = 0; i < nrPoints; i++) {
		angle += delta_angle;
		for (int j = 0; i < curvePt.size(); i++) {
			p[0] = curvePt[j][0] * cos(angle);
			p[1] = curvePt[j][1];
			p[2] = curvePt[j][2] * sin(angle);

			n[0] = curveNm[j][0] * cos(angle);
			n[1] = curveNm[j][1];
			n[2] = curveNm[j][2] * sin(angle);

			pt.push_back(p);
			nm.push_back(n);
		}
		surfaceNm.push_back(nm);
		surfacePt.push_back(pt);

	}



}

// Draws the surface given as a grid of points as a sequence of
// triangle strips.
void drawSurface(matrix3f &surfacePt, matrix3f &surfaceNm)
{

	for (int i = 0; i < (surfacePt.size() - 1); i++){

		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < surfaceNm.size(); j++) {

			surfaceNm[i][j].glNormal();
			surfacePt[i][j].glVertex();
			surfaceNm[i+1][j].glNormal();
			surfacePt[i+1][j].glVertex();
		}
		glEnd();

	}
	/*sstep = (b - a) / spoints;
	tstep = (d - c) / tpoints;
	for (i = 0; i<spoints; i++) {
		s1 = a + i * sstep;
		s2 = a + (i + 1) * sstep;
		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j <= tpoints; j++) {
			t = c + j * tstep;
			glVertex3f(x(s1, t), y(s1, t), z(s1, t));
			glVertex3f(x(s2, t), y(s2, t), z(s2, t));
		}
		glEnd();
	}*/


}














