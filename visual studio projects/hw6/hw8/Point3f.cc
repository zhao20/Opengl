/******************************************************************
Project: Creating a rotation surface in OpenGL
Dana Vrajitoru
Point3f.cc

A class to handle 3D points of GLfloat numbers.  
*******************************************************************/

#include <iostream>
using namespace std;
#include <cmath>
#include "Point3f.h"

const float epsilon = 0.00001;

// Default constructor
Point3f::Point3f(GLfloat x, GLfloat y, GLfloat z)
{
    setData(x, y, z);
}

// Constructor from a usual array.
Point3f::Point3f(GLfloat data[])
{
    setData(data);
}

// Copy constructor
Point3f::Point3f(const Point3f &data)
{
    setData(data);
}

// Destructor
Point3f::~Point3f()
{;}

// A setData function for each constructor.
// Set data with default values.
void Point3f::setData(GLfloat x, GLfloat y, GLfloat z)
{
    point[0]=x;
    point[1]=y;
    point[2]=z;
}

// Constructor from a usual array.
void Point3f::setData(GLfloat data[])
{
    for (int i=0; i<3; i++)
        point[i]=data[i];
}

// Copy constructor
void Point3f::setData(const Point3f &data)
{
    for (int i=0; i<3; i++)
        point[i]=data[i];
}

// A function that checks for the (0,0,0) point or vector.
Point3f::operator bool()
{
    return (point[0] || point[1] || point[2]);
}

// The coordinates if we want to use their names.
GLfloat &Point3f::x()
{
    return point[0];
}

GLfloat &Point3f::y()
{
    return point[1];
}

GLfloat &Point3f::z()
{
    return point[2];
}

// Assignment operator of another point.
Point3f &Point3f::operator=(const Point3f &data)
{
    if (this != &data)
        setData(data);
    return *this;
}

// Check for equality.
bool Point3f::operator==(const Point3f &data) const
{
    for (int i=0; i<3; i++)
        if (point[i] != data[i]) 
            return false;
    return true;
}

// Checks if two points are almost equal with a certain precision
// given by the parameter epsilon having the default value of 1e-6.
bool Point3f::almostEq(const Point3f &data, float eps) const
{
    for (int i=0; i<3; i++)
        if (fabs(point[i] - data[i]) > eps) {
            return false;
        }
        return true;
}

// Check for inequality.
bool Point3f::operator!=(const Point3f &data) const
{
    return !(*this==data);
}

// Access one coordinate. Check if the coordinate has a correct index.
GLfloat &Point3f::operator[](int i)
{
    if (0 <= i && i < 3)
        return point[i];
    else {
        cout << "Attempt to acces an inexistent coordinate in a point: "
            << i << endl;
        exit(1);
    }
}

// Access one coordinate. Check if the coordinate has a correct index.
GLfloat Point3f::operator[](int i) const
{
    if (0 <= i && i < 3)
        return point[i];
    else {
        cout << "Attempt to acces an inexistent coordinate in a point: "
            << i << endl;
        exit(1);
    }
}

// Add another point.
Point3f &Point3f::operator+=(const Point3f &data)
{
    for (int i=0; i<3; i++)
        point[i] += data[i];
    return *this;
}

// Substract another point.
Point3f & Point3f::operator-=(const Point3f &data)
{
    for (int i=0; i<3; i++)
        point[i] -= data[i];
    return *this;
}

// Multiply by a scalar.
Point3f & Point3f::operator *=(const float scalar)
{
    for (int i=0; i<3; i++)
        point[i] *= scalar;
    return *this;
}

// This function normalizes a vector of floats--we make it do anysize
// vector since it is easy.The size is 3 by default.
void Point3f::normalize()
{
    float d = norm(); // norm of vector
    if (d == 0.0) {
        // cerr << "Error:  Zero length vector in normalize." << endl; return;
        return;
    }
    for (int i=0; i<3; i++) 
        point[i] /= d;
}

// Computes the norm of a vector of any size.The size is 3 by default.
float Point3f::norm()
{
    float d = 0.0;
    for (int i=0; i<3; i++) 
        d += point[i]*point[i];
    d = sqrt(d);
    return d;
}

// Computes the scalar product of two vectors of any size. The size is
// 3 by default.
float Point3f::scalarprod(const Point3f &other)
{
    float prod = 0.0;
    int i;

    for (i=0; i<3; i++)
        prod += point[i]*other[i];
    return prod;
}

// This function computes the normal to the plane determined by the 
// three points v0,v1,v2 (3 vectors).  I.e. it computes the cross product
// of of (v0-v1) and (v1-v2).
// It is assumed that all four vectors have length three (no checking is done)
void Point3f::computeNormalVector(const Point3f &v0, const Point3f &v1, 
    const Point3f &v2)
{ 
    Point3f d1, d2;
    for (int i=0; i<3; i++) {
        d1[i] = v0[i]-v1[i]; 
        d2[i] = v1[i]-v2[i];
    }
    normcrossprod(d1, d2);
}

// this function computes the normaalized cross product of two vectors.
// It is assumed that all three vectors have length three (no checking is done)
void Point3f::normcrossprod(const Point3f &v1, const Point3f &v2)
{
    point[0] = v1[1]*v2[2] - v1[2]*v2[1];
    point[1] = v1[2]*v2[0] - v1[0]*v2[2];
    point[2] = v1[0]*v2[1] - v1[1]*v2[0];
    normalize();
}

// Checks if two vectors are colinear.
bool Point3f::colinearXz(const Point3f q) const
{
    return (point[0] * q[2] - point[2] * q[0] == 0);
}

// Checks if the target object is on the line given by an origin and a
// direction.
bool Point3f::onLineXz(const Point3f &q, const Point3f &d1) const
{
    Point3f p(*this);
    p -= q;
    return (p.colinearXz(d1));
}

// Intersection between two lines. The returned value is the solution
// of the equation over u: intersection = *this + ud.
float Point3f::intersectXz(const Point3f &d, 
    const Point3f &q, const Point3f &d1) const
{
    Point3f p(q);
    p -= *this;

    if (fabs(d1[0]*d[2] - d1[2]*d[0]) <= epsilon) { // d and d1 parallel
        if (fabs(p[0]*d[2] - p[2]*d[0]) <= epsilon) // d and d1 colinear
            if (d[0]*d1[0] >= 0) // d and d1 in the same direction
                return 1;
            else
                return 0;
        else
            return -1;
    }
    else {
        float v=(p[2]*d[0] - p[0]*d[2]) / (d1[0]*d[2] - d1[2]*d[0]);
        if (fabs(d[0]) <= epsilon)
            return (v * d1[2] + p[2])/d[2];
        else
            return (v * d1[0] + p[0])/d[0];
    }
}

// The usual Euclidian distance.
float Point3f::distance(const Point3f &p1) const
{
    return sqrt((p1[0] - point[0]) * (p1[0] - point[0]) + 
                (p1[1] - point[1]) * (p1[1] - point[1]) +
                (p1[2] - point[2]) * (p1[2] - point[2]));
}

// Perform an OpenGL rotation and translation based on the point.
void Point3f::glRotate() const
{
    glRotatef(point[0], 1, 0, 0);
    glRotatef(point[1], 0, 1, 0);
    glRotatef(point[2], 0, 0, 1);
}

void Point3f::glTranslate() const
{
    glTranslatef(point[0], point[1], point[2]);
}

// Make a GL vertex of this point.
void Point3f::glVertex() const
{
    glVertex3f(point[0], point[1], point[2]);
}

// Make a GL normal of this point.
void Point3f::glNormal() const
{
    glNormal3f(point[0], point[1], point[2]);
}

// Rotate by an arbitrary angle around one of the 3 main axes. All the
// angles should be in radians.
void Point3f::rotateX(float angle)
{
    Point3f temp;
    temp[0]=point[0];
    temp[1]=cos(angle)*point[1] - sin(angle)*point[2];
    temp[2]=sin(angle)*point[1] + cos(angle)*point[2];
    setData(temp);
}

void Point3f::rotateY(float angle)
{
    Point3f temp;
    temp[0] = cos(angle)*point[0] - sin(angle)*point[2];
    temp[1] = point[1];
    temp[2] = sin(angle)*point[0] + cos(angle)*point[2];
    setData(temp);
}

void Point3f::rotateZ(float angle)
{
    Point3f temp;
    temp[0] = cos(angle)*point[0] - sin(angle)*point[1];
    temp[1] = sin(angle)*point[0] + cos(angle)*point[1];
    temp[2] = point[2];
    setData(temp);
}

// Tells us if the other point and the target object (this) are on the
// same side of the line l1 l2.
bool Point3f::sameSideXz(const Point3f &l1, const Point3f &l2, 
    const Point3f &other) const
{
    return (((point[0] - l1[0]) * (l2[2] - l1[2]) 
             - (l2[0] - l1[0]) * (point[2] - l1[2]))
            * ((other[0] - l1[0]) * (l2[2] - l1[2]) 
               - (l2[0] - l1[0]) * (other[2] - l1[2])) >= 0);
}

// Tells us if the target object is inside the triangle defined by the
// 3 arguments.
bool Point3f::insideXz(const Point3f &p1, const Point3f &p2, 
    const Point3f &p3) const
{
    return (sameSideXz(p1, p2, p3) &&
            sameSideXz(p2, p3, p1) &&
            sameSideXz(p3, p1, p2));
}

// Initializes the current point as a unit vector orthogonal to the
// one given as a parameter in the xy plane.
void Point3f::orthogonalXy(const Point3f &p)
{
    // rotating x and y by 90 degrees.
    point[0] = p[1];
    point[1] = -p[0];
    // we're not concerned with z so we're just copying it.
    point[2] = p[2]; 
    // Make the current point a unit vector.
    normalize();
}

// Easy output of a point. No message, just spaces between numbers.
ostream &operator<<(ostream &out, const Point3f &data)
{
    out << data[0] << ' ' << data[1] << ' ' << data[2];
    return out;
}

// The distance between two points;
float distance(const Point3f &p1, const Point3f &p2)
{
    return sqrt((p1[0]-p2[0])*(p1[0]-p2[0]) + 
                (p1[1]-p2[1])*(p1[1]-p2[1]) +
                (p1[2]-p2[2])*(p1[2]-p2[2]));
}
