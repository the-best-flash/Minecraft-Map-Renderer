/************************************************************************
Program:     Project 2, Solar System Simulation
Author:      Colton Manville, Jordan Neumeyer
Class:       Computer Graphics
Instructor:  Dr. Weiss
Date:        10/28/2010
Description: This program simulates the 8 planets rotating around the sun.
             The user can zoom in, rotate about the sun, and rotate above
			 and below the orbital plane.
			 This program also allows the user to speed up and slow down
			 the simulation, as well as allowing the user to pause the
			 simulation and step the simulation forward and backward in
			 fixed time increments.
Input:       None
Output:      None
Compilation instructions:
Usage:       p    - Pauses the simulation
             s    - Restarts the simulation after it has been paused
			 +    - increases the speed of the simulation
			 -    - decreases the speed of the simulation
			 [    - steps the simulation backward when it is paused
			 ]    - steps the simulation backward when it is paused
			 PgUp - increases the camera's angle of elevation above the
			        orbital plane
		     PgDn - decreases the camera's angle of elevation about the
			        orbital plane
			 UP   - moves the camera closer to the sun
			 DOWN - Moves the camera farther from the sun
			 LEFT - Rotates the camera clockwise about the sun
			 RIGHT - Rotates the camera counter-clockwise about the sun
			 esc   - Exits the program
Known bugs/missing features:
Modifications: Added 4 of Jupiter's largest moons
               Added text to the planets
************************************************************************/

#ifndef _POINT_H_
#define _POINT_H_

template <typename T>
struct Point
{
    T x;
    T y;
	T z;

    Point(T x = 0, T y = 0, T z = 0 );
    Point(const Point<T>& point);

    Point<T> operator-(const Point<T>& p) const;
    Point<T> operator+(const Point<T>& p) const;
    Point<T> operator*(const Point<T>& p) const;
    Point<T> operator/(const Point<T>& p) const;

    Point<T> operator-(const T f) const;
    Point<T> operator+(const T f) const;
    Point<T> operator*(const T f) const;
    Point<T> operator/(const T f) const;

    Point<T>& operator/=(const Point<T>& p);
    Point<T>& operator-=(const Point<T>& p);
    Point<T>& operator+=(const Point<T>& p);
    Point<T>& operator*=(const Point<T>& p);

    Point<T>& operator/=(const T f);
    Point<T>& operator-=(const T f);
    Point<T>& operator+=(const T f);
    Point<T>& operator*=(const T f);

    const Point<T>& operator=(const Point<T>& p);
};

template <typename T>
Point<T>::Point( T x, T y, T z )
    : x(x),
      y(y),
	  z(z)
{ }

template <typename T>
Point<T>::Point( const Point<T>& p)
    : x(p.x),
      y(p.y),
	  z(p.z)
{ }

template <typename T>
Point<T> Point<T>::operator-(const Point<T>& p) const
{
    return Point<T>( x - p.x, y - p.y, z - p.z);
}

template <typename T>
Point<T> Point<T>::operator+(const Point<T>& p) const
{
    return Point<T>( x + p.x, y + p.y, z + p.z);
}

template <typename T>
Point<T> Point<T>::operator*(const Point<T>& p) const
{
    return Point<T>( x * p.x, y * p.y, z * p.z);
}

template <typename T>
Point<T> Point<T>::operator/(const Point<T>& p) const
{
    return Point<T>( x / p.x, y / p.y, z / p.z);
}

template <typename T>
Point<T> Point<T>::operator-(const T f) const
{
    return Point<T>(x - f, y - f, z - f);
}

template <typename T>
Point<T> Point<T>::operator+(const T f) const
{
    return Point<T>(x + f, y + f, z + f);
}

template <typename T>
Point<T> Point<T>::operator*(const T f) const
{
    return Point<T>(x * f, y * f, z * f);
}

template <typename T>
Point<T> Point<T>::operator/(const T f) const
{
    return Point<T>(x / f, y / f, z / f);
}

template <typename T>
Point<T>& Point<T>::operator/=(const Point<T>& p)
{
    x /= p.x;
    y /= p.y;
	z /= p.z;

    return *this;
}

template <typename T>
Point<T>& Point<T>::operator-=(const Point<T>& p)
{
    x -= p.x;
    y -= p.y;
	z -= p.z;

    return *this;
}

template <typename T>
Point<T>& Point<T>::operator+=(const Point<T>& p)
{
    x += p.x;
    y += p.y;
	z += p.z;

    return *this;
}

template <typename T>
Point<T>& Point<T>::operator*=(const Point<T>& p)
{
    x *= p.x;
    y *= p.y;
	z *= p.z;

    return *this;
}

template <typename T>
Point<T>& Point<T>::operator/=(const T f)
{
    x /= f;
    y /= f;
	z /= f;

    return *this;
}

template <typename T>
Point<T>& Point<T>::operator-=(const T f)
{
    x -= f;
    y -= f;
	z -= f;

    return *this;
}

template <typename T>
Point<T>& Point<T>::operator+=(const T f)
{
    x += f;
    y += f;
	z += f;

    return *this;
}

template <typename T>
Point<T>& Point<T>::operator*=(const T f)
{
    x *= f;
    y *= f;
	z *= f;

    return *this;
}

template <typename T>
const Point<T>& Point<T>::operator=(const Point<T>& p)
{
    x = p.x;
    y = p.y;
	z = p.z;

    return p;
}

#endif
