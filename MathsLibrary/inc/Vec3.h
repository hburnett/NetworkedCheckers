//! Author: Heath Burnett
//! Credit to Aaron Cox for assisting in the creation
//
//! Description: Vector 3D Math Lib Class
//! Allows for an object to have a 3rd dimension


#ifndef VEC3_H
#define VEC3_H

#include <math.h>

class Vec3
{
public:
	
	//Default Constructor
	Vec3();

	//! Vec3(float X, float Y, float Z);
	//! Overloaded Constructor
	//! Sets x, y and z to the X, Y and Z values passed in
	Vec3(float X, float Y, float Z);
	
	//! Vec3 operator + (const Vec3 &rhs) const;
	//! Allows the addition of two Vec3's
	Vec3 operator + (const Vec3 &rhs) const;
	
	//! Vec3 operator - (const Vec3 &rhs) const;
	//! Allows the subtraction of two Vec3's
	Vec3 operator - (const Vec3 &rhs) const;
	
	//! Vec3 operator * (const Vec3 &rhs) const;
	//! Allows the multiplication of two Vec3's
	Vec3 operator * (const Vec3 &rhs) const;
	
	//! Vec3 operator * (float rhs) const;
	//! Allows the multiplication of a Vec3 by a floating point number
	//! x, y and z are each multiplied by the value passed in
	Vec3 operator * (float rhs) const;
	
	//! Vec3 operator / (const Vec3 &rhs) const;
	//! Allows the division of one Vec3 by another
	Vec3 operator / (const Vec3 &rhs) const;
	
	//! Vec3 operator / (float rhs) const;
	//! Allows the division of a Vec3 by a floating point number
	//! x, y and z are each divided by the value passed in
	Vec3 operator / (float rhs) const;
	
	//! Vec3& operator += (const Vec3 &rhs);
	//! Allows the compound addition of two Vec3's
	Vec3& operator += (const Vec3 &rhs);
	
	//! Vec3& operator -= (const Vec3 &rhs);
	//! Allows the compound subtraction of two Vec3's
	Vec3& operator -= (const Vec3 &rhs);
	
	//! Vec3& operator *= (const Vec3 &rhs);
	//! Allows the compound multiplication of two Vec3's
	Vec3& operator *= (const Vec3 &rhs);
	
	//! Vec3& operator *= (float rhs);
	//! Allows the compound multiplication of a floating point number
	//! x, y and z are each multiplied by the value passed in
	Vec3& operator *= (float rhs);
	
	//! Vec3& operator /= (const Vec3 &rhs);
	//! Allows the compound division of two Vec3's
	Vec3& operator /= (const Vec3 &rhs);
	
	//! Vec3& operator /= (float rhs);
	//! Allows the compound division of a Vec3 by a floating point number
	//! x, y and z are each divided by the value passed in
	Vec3& operator /= (float rhs);
	
	//! float Length();
	//! Squares x, y and z seperately, adds them all together 
	//! Then returns the square roots of that value
	float Length();
	
	//! void Normalise();
	//! Normalises the values of x, y and z to a scale from 0 to 1
	//! Calls the length function then divides x, y and z by the length
	//! If the length is 0, nothing happens, stops divide by 0 errors
	void Normalise();
	
	//! float DotProduct(const Vec3 &rhs);
	//! Multiplies x, y and z of the Vec3 calling the function,
	//! With the x, y and z of the Vec3 passed in
	//! Then adds all the multiplications together and returns the result
	float DotProduct(const Vec3 &rhs);
	
	//! float AngleBetween(const Vec3 &rhs);
	//! Creates a perpendicular angle Vec3 at the inverse position of the object
	//! Then finds the angle between the object and the Vec3 passed in using cos and DotProduct
	//! Checks this angle against the perpendicular angle to calculate whether it is positive or negative
	float AngleBetween(const Vec3 &rhs);
	
	//variables
	float m_fAngle;
	float x;
	float y;
	float z;

protected:
private:

};


#endif