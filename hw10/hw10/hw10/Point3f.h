/******************************************************************
Project: Creating a rotation surface in OpenGL
Dana Vrajitoru
Point3f.h

A class to handle 3D points of GLfloat numbers.  
*******************************************************************/

#ifndef POINT3F_H
#define POINT3F_H

#include "glheader.h"
#include <vector>
#include <iostream>
using namespace std;

class Point3f {
private:
    GLfloat point[3];

public:
    // Constructor with default values.
    Point3f(GLfloat x=0.0, GLfloat y=0.0, GLfloat z=0.0);
    // Constructor from a usual array.
    Point3f(GLfloat data[]);
    // Copy constructor
    Point3f(const Point3f &data);
    // Destructor
    ~Point3f();

    // A setData function for each constructor.
    // Set data with default values.
    void setData(GLfloat x=0.0, GLfloat y=0.0, GLfloat z=0.0);
    // Constructor from a usual array.
    void setData(GLfloat data[]);
    // Copy constructor
    void setData(const Point3f &data);

    // A function that checks for the (0,0,0) point or vector.
    operator bool();

    // The coordinates if we want to use their names.
    GLfloat &x();
    GLfloat &y();
    GLfloat &z();

    // Assignment operator of another point.
    Point3f &operator=(const Point3f &data);
    // Check for equality.
    bool operator==(const Point3f &data) const;
    // Checks if two points are almost equal with a certain precision
    // given by the parameter epsilon having the default value of 1e-6.
    bool almostEq(const Point3f &data, float eps=0.0005) const;
    // Check for inequality.
    bool operator!=(const Point3f &data) const;
    // Access one coordinate. Check if the coordinate has a correct
    // index.
    GLfloat &operator[](int i);
    // Access one coordinate. Check if the coordinate has a correct
    // index.
    GLfloat operator[](int i) const;
    // Add another point.
    Point3f &operator+=(const Point3f &data);
    // Substract another point.
    Point3f &operator-=(const Point3f &data);
    // Multiply by a scalar.
    Point3f &operator*=(const float scalar);

    // This function normalizes a vector of floats--we make it do anysize
    // vector since it is easy.The size is 3 by default.
    void normalize();

    // Computes the norm of a vector of any size.The size is 3 by default.
    float norm();

    // Computes the scalar product of two vectors of any size. The size is
    // 3 by default.
    float scalarprod(const Point3f &other);
    // This function computes the normal to the plane determined by the
    // three points v0,v1,v2 (3 vectors).  I.e. it computes the cross
    // product of of (v0-v1) and (v1-v2).  It is assumed that all four
    // vectors have length three (no checking is done)
    void computeNormalVector(const Point3f &v0, const Point3f &v1, 
                             const Point3f &v2);
    // this function computes the normalized cross product of two
    // vectors.  It is assumed that all three vectors have length three
    // (no checking is done)
    void normcrossprod(const Point3f &v1, const Point3f &v2);
    // The distance between two points;
    float distance(const Point3f &p1) const;
    // Checks if two vectors are colinear.
    bool colinearXz(const Point3f q) const;
    // Checks if the target object is on the line given by an origin and
    // a direction.
    bool onLineXz(const Point3f &q, const Point3f &d1) const;
    // Intersection between two lines
    float intersectXz(const Point3f &dir, 
                      const Point3f &q, const Point3f &d1) const;

    // Perform an OpenGL rotation and translation based on the point.
    void glRotate() const;
    void glTranslate() const;
    // Make a GL vertex or normal of this point.
    void glVertex() const;
    void glNormal() const;

    // Rotate by an arbitrary angle around one of the 3 main axes.
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    // Tells us if the other point and the target object (this) are on
    // the same side of the line l1 l2.
    bool sameSideXz(const Point3f &l1, const Point3f &l2, 
                    const Point3f &other) const;

    // Tells us if the target object is inside the triangle defined by
    // the 3 arguments.
    bool insideXz(const Point3f &p1, const Point3f &p2, 
        const Point3f &p3) const;

    // Initializes the current point as a unit vector orthogonal to the
    // one given as a parameter.
    void orthogonalXy(const Point3f &p1);

    // Easy output of a point. No message, just spaces between numbers.
    friend ostream &operator<<(ostream &out, const Point3f &data);
    friend float distance(const Point3f &p1, const Point3f &p2);
};

typedef vector<Point3f> vector3f;
typedef vector<vector3f> matrix3f;

#endif
