//! Author: Heath Burnett
//! Description: Matrix 3x3 class

#ifndef	MAT3_H
#define	MAT3_H


class Vec2;

class Mat3
{
public:

	float m1, m2, m3,
		  m4, m5, m6,
		  m7, m8, m9;
	
	//! void Mat3() - Constructor;
	//! Creates the base identity matrix, setting all values to default
	//! 1 0 0
	//! 0 1 0
	//! 0 0 1
	Mat3(){		  m1 = 1; m2 = 0; m3 = 0; 
				  m4 = 0; m5 = 1; m6 = 0;
				  m7 = 0; m8 = 0; m9 = 1;	}

	//! void CreateIdentity();
	//! Creates the base identity matrix, setting all values to default
	void CreateIdentity();
	
	//Translation stuff

	//! void SetTranslation(float tX, float tY);
	//! Sets the translation of an object to the values passed in
	//! Best used for static objects
	void SetTranslation(float tX, float tY);
	
	//! void SetTranslation( Vec2 vec );
	//! Sets the translation of an object to the values passed in
	//! Best used for static objects
	void SetTranslation( Vec2 translation );

	//! void AddTranslation(float tX, float tY);
	//! Adds the values passed in to the translation of the object
	//! Best used for moving objects
	void AddTranslation(float tX, float tY);
	
	//! void AddTranslation( Vec2 vec );
	//! Adds the values passed in to the translation of the object
	//! Best used for moving objects
	void AddTranslation( Vec2 translation );
	
	//! Vec2 GetTranslation() const;
	//! Gets the translation of the object, returning a Vec2
	Vec2 GetTranslation() const;

	//Rotation stuff

	//!void Mat3::SetRotation( float rot );
	//! Creates the objects rotation
	//! All rotation values are in radians, not degree
	void Mat3::CreateRotation( float rot );

	//! void SetRotation(float rot);
	//! Sets the rotation of the object to the value passed in
	//! All rotation values are in radians, not degrees
	void SetRotation(float rot);
	
	//! void SetRotation( Vec2 rotVec );
	//! Sets the rotation of the object to the value passed in
	//! All rotation values are in radians, not degrees
	void SetRotation( Vec2 rotVec );
	
	//! void AddRotation(float rot);
	//! Add the rotation of the object to the value passed in	
	//! All rotation values are in radians, not degrees
	void AddRotation(float rot);
	
	//! Vec2 GetRotation( ) const;
	//! Gets the rotation of the object, returning a Vec2
	//! All rotation values are in radians, not degrees
	Vec2 GetRotation( ) const;

	//! Vec2 GetDirection() const;
	//! Returns a Vec2 of the objects direction
	//! For example: An object at a 45 degree angle has an up rotation of .707 in x and .707 in y.
	//! The other GetRotation functions get the objects rotation, relative to the world not itself
	Vec2 GetDirection() const;
	
	//! float GetUpRotation() const;
	//! Gets the objects Up rotation, relative to the world, returning a float
	float GetUpRotation() const;
	
	//! float GetRightRotation() const;
	//! Gets the objects Right rotation, relative to the world, returning a float
	float GetRightRotation() const;

	//Scale stuff
	
	//! void SetScale(float sX, float sY);
	//! Sets the scale of an object to the new scale
	void SetScale(float sX, float sY);

	//! void SetScale(float sX, float sY);
	//! Sets the scale of an object to the new scale
	void SetScale( Vec2 scale );

	//! void AddScale( float sX, float sY );
	//! Adds the variable passed in to the current scale
	void AddScale( float sX, float sY );
	
	void AddScale( Vec2 scale );

	//! Vec2 GetScale() const;
	//! Gets the scale of object, returning a Vec2
	Vec2 GetScale() const;
	
	//! float GetUpScale() const;
	//! Gets the Up scale of object, returning a float
	float GetUpScale() const;
	
	//! float GetRightScale() const;
	//! Gets the Right scale of object, returning a float
	float GetRightScale() const;
	
	//! Mat3 operator * (const Mat3 &rhs) const;
	//! Allows the multiplication of two Mat3's
	Mat3 operator * (const Mat3 &rhs) const;
	
	//! Mat3 &operator *=(const Mat3 &rhs);
	//! Allows the compound multiplication of two Mat3's
	Mat3 &operator *=(const Mat3 &rhs);
	
	//! Vec2 operator * (const Vec2 &rhs) const;
	//! Allows the multiplication of a Mat3 by a Vec2
	//! Returns a Vec2
	Vec2 operator * (const Vec2 &rhs) const;
	
	//! bool operator ==( const Mat3 &rhs) const;
	//! Allows a boolean check to see if two Mat3's are identical
	//! Returns true if they are
	bool operator ==( const Mat3 &rhs) const;
	
	//! bool operator !=( const Mat3 &rhs) const;
	//! Allows a boolean check to see if two Mat3's are different
	//! Returns true if they are
	bool operator !=( const Mat3 &rhs) const;



};

#endif