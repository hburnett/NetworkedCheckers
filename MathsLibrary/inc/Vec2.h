//! Author: Heath Burnett
//! Credit to Aaron Cox
//
//! Description: Vector 2D Math Lib Class
//
#ifndef VEC2_H
#define VEC2_H

class Mat3;

class Vec2
{
public:
	
	//Default Constructor
	Vec2();

	//! Vec2(float X, float Y);
	//! Overloaded Constructor
	//! Sets x and y to the X and Y values passed in
	Vec2(float X, float Y);

	//! Vec2 operator + (const Vec2 &rhs) const;
	//! Allows the addition of two Vec2's
	Vec2 operator + (const Vec2 &rhs) const;

	//! Vec2 operator - (const Vec2 &rhs) const;
	//! Allows the subtraction of two Vec2's
	Vec2 operator - (const Vec2 &rhs) const;
	
	//! Vec2 operator * (const Vec2 &rhs) const;
	//! Allows the multiplication of two Vec2's
	Vec2 operator * (const Vec2 &rhs) const;
	
	//! Vec2 operator * (float rhs) const;
	//! Allows the multiplication of a Vec2 by a floating point number
	//! x and y  are each multiplied by the value passed in
	Vec2 operator * (float rhs) const;
	
	//! Vec2 operator * (const Mat3 &rhs) const;
	//! Allows the multiplication of a Vec2 by a Mat3
	//! Returns a Vec2 of the first two columns
	Vec2 operator * (const Mat3 &rhs) const;
	
	//! Vec2 operator / (const Vec2 &rhs) const;
	//! Allows the division of one Vec2 by another
	Vec2 operator / (const Vec2 &rhs) const;
	
	//! Vec2 operator / (float rhs) const;
	//! Allows the division of a Vec2 by a floating point number
	//! x and y  are each divided by the value passed in
	Vec2 operator / (float rhs) const;
	
	//! Vec2& operator += (const Vec2 &rhs);
	//! Allows the compound addition of two Vec2's
	Vec2& operator += (const Vec2 &rhs);
	
	//! Vec2& operator -= (const Vec2 &rhs);
	//! Allows the compound subtraction of two Vec2's
	Vec2& operator -= (const Vec2 &rhs);
	
	//! Vec2& operator *= (const Vec2 &rhs);
	//! Allows the compound multiplication of two Vec2's
	Vec2& operator *= (const Vec2 &rhs);
	
	//! Vec2& operator *= (float rhs);
	//! Allows the compound multiplication of a floating point number
	//! x and y  are each multiplied by the value passed in
	Vec2& operator *= (float rhs);
	
	//! Vec2& operator /= (const Vec2 &rhs);
	//! Allows the compound division of two Vec2's
	Vec2& operator /= (const Vec2 &rhs);
	
	//! Vec2& operator /= (float rhs);
	//! Allows the compound division of a Vec2 by a floating point number
	//! x and y  are each divided by the value passed in
	Vec2& operator /= (float rhs);
	
	//! float Length();
	//! Squares x and y  seperately, adds them all together 
	//! Then returns the square roots of that value
	float Length();
	
	//! void Normalise();
	//! Normalises the values of x and y  to a scale from 0 to 1
	//! Calls the length function then divides x and y  by the length
	//! If the length is 0, nothing happens, stops divide by 0 errors
	void Normalise();
	
	//! float DotProduct(const Vec2 &rhs);
	//! Multiplies x and y  of the Vec2 calling the function,
	//! With the x and y  of the Vec2 passed in
	//! Then adds all the multiplications together and returns the result
	float DotProduct(const Vec2 &rhs);
	
	//! float AngleBetween360Degrees(const Vec2 &rhs, bool returnDegree);
	//! Calculates the angle between by using cos(angle) = Y2 - Y1 / X2 - X1
	//! Returns in either degrees or radians
	//! Full 360 degrees is used so a little to the left is 345 degrees not 15
	float AngleBetween360Degrees(const Vec2 &rhs, bool returnDegree);
	
	//! float AngleBetween180Degrees(const Vec2 &rhs, bool returnDegree);
	//! Calculates the angle between by using cos(angle) = Y2 - Y1 / X2 - X1
	//! Returns in either degrees or radians
	//! 180 degrees is used so a little to the left is 15 degrees not 345
	float AngleBetween180Degrees(const Vec2 &rhs, bool returnDegree);
	
	// Variables
	float x;
	float y;

protected:
private:

};


#endif