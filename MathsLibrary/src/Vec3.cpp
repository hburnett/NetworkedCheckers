#include "Vec3.h"
#include <math.h>
#include <stdlib.h>


Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
};

Vec3::Vec3(float X, float Y, float Z) : x(X), y(Y), z(Z)
{
	m_fAngle = 0;
}

Vec3 Vec3::operator + (const Vec3 &rhs) const
{
	return Vec3( x + rhs.x, y + rhs.y, z + rhs.z );
}

Vec3 Vec3::operator - (const Vec3 &rhs) const
{
	return Vec3( x - rhs.x, y - rhs.y, z - rhs.z );
}

Vec3 Vec3::operator * (const Vec3 &rhs) const
{
	return Vec3( x * rhs.x, y * rhs.y, z * rhs.z );
}

Vec3 Vec3::operator * (float rhs) const
{
	return Vec3( x * rhs, y * rhs, z * rhs );
}

Vec3 Vec3::operator / (const Vec3 &rhs) const
{
	return Vec3( x / rhs.x, y / rhs.y, z / rhs.z );
}

Vec3 Vec3::operator / (float rhs) const
{
	return Vec3( x / rhs, y / rhs, z / rhs );
}

Vec3& Vec3::operator += (const Vec3 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vec3& Vec3::operator -= (const Vec3 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vec3& Vec3::operator *= (const Vec3 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

Vec3& Vec3::operator *= (float rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

Vec3& Vec3::operator /= (const Vec3 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

Vec3& Vec3::operator /= (float rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

float Vec3::Length()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

void Vec3::Normalise()
{
	float length = Length();
	if( length != 0)
	{
		x /= length;
		y /= length;
		z /= length;
	}
}


float Vec3::DotProduct(const Vec3 &rhs)
{
	return ((x * rhs.x) + (y * rhs.y) + (z * rhs.z));
}

float Vec3::AngleBetween(const Vec3 &rhs)
{
	//Creates a vector who is perpendicular to the Vector calling the function
	Vec3 PerpendicularAngle;
	PerpendicularAngle.x = y;
	PerpendicularAngle.y = -x;
	PerpendicularAngle.z = z;

	//Finds the angle between the Vector calling the function and the parameter it calls.
	//Eg: A.AngleBetween(B) finds the angle between A and B, starting at A.
	m_fAngle = acosf(this->DotProduct(rhs));

	//Determines whether the angle is positive or negative
	if(PerpendicularAngle.DotProduct(rhs) < 0)
		m_fAngle = -m_fAngle;

	return m_fAngle;
	
}