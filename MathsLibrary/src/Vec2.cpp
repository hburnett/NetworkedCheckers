#include "Vec2.h"
#include "Mat3.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

//Default Constructor
Vec2::Vec2() :	x(0), y(0)
{
};

//Overloaded Constructor
Vec2::Vec2(float X, float Y) : x(X), y(Y)
{
}


Vec2 Vec2::operator + (const Vec2 &rhs) const
{
	return Vec2( x + rhs.x, y + rhs.y );
}

Vec2 Vec2::operator - (const Vec2 &rhs) const
{
	return Vec2( x - rhs.x, y - rhs.y );
}

Vec2 Vec2::operator * (const Vec2 &rhs) const
{
	return Vec2( x * rhs.x, y * rhs.y );
}

Vec2 Vec2::operator * (float rhs) const
{
	return Vec2( x * rhs, y * rhs );
}

Vec2 Vec2::operator * (const Mat3 &rhs) const
{
	return Vec2( (x * rhs.m1) + (y * rhs.m4) + rhs.m7, (x * rhs.m2) + (y * rhs.m5) + rhs.m8);
}

Vec2 Vec2::operator / (const Vec2 &rhs) const
{
	return Vec2( x / rhs.x, y / rhs.y );
}

Vec2 Vec2::operator / (float rhs) const
{
	return Vec2( x / rhs, y / rhs );
}

Vec2& Vec2::operator += (const Vec2 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2& Vec2::operator -= (const Vec2 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

//Vector
Vec2& Vec2::operator *= (const Vec2 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

//Scalar
Vec2& Vec2::operator *= (float rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

//Vector
Vec2& Vec2::operator /= (const Vec2 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

//Scalar
Vec2& Vec2::operator /= (float rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}

float Vec2::Length()
{
	return sqrt(x * x + y * y);
}

void Vec2::Normalise()
{
	float length = Length();
	if( length != 0)
	{
		x /= length;
		y /= length;
	}
}

float Vec2::DotProduct(const Vec2 &rhs)
{
	return ((x * rhs.x) + (y * rhs.y));
}

float Vec2::AngleBetween360Degrees(const Vec2 &rhs, bool returnDegree)
{
	//Vec2 left	= *this;
	//Vec2 right	= rhs;
	////
	////left.Normalise();
	////right.Normalise();
	//
	//float LeftLength = this->Length();
	//float RightLength = right.Length();
	//
	////Creates a vector who is perpendicular to the Vector calling the function
	//Vec2 PerpendicularAngle;
	//PerpendicularAngle.x = y;
	//PerpendicularAngle.y = -x;
	//
	//float dotAB = this->DotProduct(right);
	//
	////Finds the angle between the Vector calling the function and the parameter it calls.
	////Eg: A.AngleBetween(B) finds the angle between A and B, starting at A.
	//float fAngle = acosf( dotAB / ( LeftLength * RightLength ) );
	//
	////Determines whether the angle is positive or negative
	//if(PerpendicularAngle.DotProduct(right) < 0)
	//	fAngle = -fAngle;
	//
	//return fAngle;

	float XLength =  rhs.x - x;
	float YLength =  rhs.y - y;
	
	float absXLength = abs(XLength);
	float absYLength = abs(YLength);

	float fAngle = (M_PI / 2) - atan( absYLength / absXLength );

	//Quadrant 2
	if( XLength >= 0 && YLength < 0 )
	{
		fAngle = (M_PI) - fAngle;
	}
	
	//Quadrant 3
	else if( XLength <= 0 && YLength < 0 )
	{
		fAngle = fAngle + (M_PI);
	}

	//Quadrant 4
	else if( XLength < 0 && YLength > 0 )
	{
		fAngle = (M_PI * 2) - fAngle;
	}

	if( returnDegree )
		fAngle = (fAngle * 180) / M_PI;

	return fAngle;	
}


float Vec2::AngleBetween180Degrees(const Vec2 &rhs, bool returnDegree)
{
	float XLength =  rhs.x - x;
	float YLength =  rhs.y - y;
	
	float absXLength = abs(XLength);
	float absYLength = abs(YLength);

	float fAngle = (M_PI / 2) - atan( absYLength / absXLength );


	//Quadrant 2
	if( YLength <= 0 )
	{
		fAngle = (M_PI) - fAngle;
	}	
	
	if( returnDegree )
		fAngle = (fAngle * 180) / M_PI;

	return fAngle;
	
}	