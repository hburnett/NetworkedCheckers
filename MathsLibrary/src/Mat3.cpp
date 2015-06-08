#include "Mat3.h"
#include "Vec2.h"
#include <math.h>

void Mat3::CreateIdentity()
{
	m1 = 1; m2 = 0; m3 = 0;
	m4 = 0; m5 = 1; m6 = 0;
	m7 = 0; m8 = 0; m9 = 1;
}

//Translation stuff
void Mat3::SetTranslation(float tX, float tY)
{
	m7 = tX; m8 = tY;
}

void Mat3::SetTranslation( Vec2 translation )
{
	m7 = translation.x;  m8 = translation.y; 
}

void Mat3::AddTranslation(float tX, float tY)
{
	m7 += tX;	m8 += tY;
}

void Mat3::AddTranslation( Vec2 translation )
{
	m7 += translation.x;  m8 += translation.y;
}

Vec2 Mat3::GetTranslation() const
{
	return Vec2(m7, m8);
}

//Rotation stuff
void Mat3::CreateRotation( float rot )
{
	m1 = cos(rot); 
	m2 = -sin(rot);

	m4 = sin(rot);
	m5 = cos(rot); 
}

void Mat3::SetRotation(float rot)
{
	Vec2 axisScale = GetScale();
	
	m1 = cos(rot); 
	m1 *= axisScale.x;

	m2 = -sin(rot); 
	m2 *= axisScale.x; 

	m4 = sin(rot); 
	m4 *= axisScale.y;

	m5 = cos(rot); 
	m5 *= axisScale.y;  
}

void Mat3::SetRotation( Vec2 rotVec )
{
	Vec2 axisScale = GetScale();

	rotVec.Normalise();
	
	m1 = cos( rotVec.x ); 
	m1 *= axisScale.x;

	m2 = -sin( rotVec.x ); 
	m2 *= axisScale.x; 

	m4 = sin( rotVec.y ); 
	m4 *= axisScale.y;

	m5 = cos( rotVec.y ); 
	m5 *= axisScale.y;  
}

void Mat3::AddRotation(float rot)
{

	Mat3 rotMat;
	rotMat.CreateRotation(rot);

	*this = rotMat * *this;

	/*Vec2 Scale = GetScale();
	
	float upRotation = GetUpRotation();
	float rightRotation = GetRightRotation();
	
	m1 = cos(rot + rightRotation);
	m1 *= Scale.x;
	
	m2 = -sin(rot + rightRotation);
	m2 *= Scale.x;
	
	m4 = sin((rot + upRotation)); 
	m4 *= Scale.y;
	
	m5 = cos(rot + upRotation); 
	m5 *= Scale.y;*/
}

//Need something to determine where the angle is.
//When scaling, angle is kept but can be flipped
//Technically the same angle, but not the same position

Vec2 Mat3::GetRotation() const
{
	return Vec2( GetRightRotation(), GetUpRotation() );
}

float Mat3::GetUpRotation() const
{
	Vec2 worldUp(0, 1);

	Vec2 upRotation(m4, m5);

	upRotation.Normalise();

	return worldUp.AngleBetween360Degrees(upRotation, false);
}

Vec2 Mat3::GetDirection() const
{
	Vec2 direction(m4, m5);

	direction.Normalise();

	return direction;

}

float Mat3::GetRightRotation() const
{	
	Vec2 worldRight(1, 0);

	Vec2 rightRotation(m1, m2);

	rightRotation.Normalise();

	return worldRight.AngleBetween360Degrees(rightRotation, false);
}

//Scale stuff
void Mat3::SetScale(float sX, float sY)
{
	Vec2 axisScale = GetScale();

	//Ff the scale is negative the image will reverse
	//and flicker between upright and upside down.
	//To combat this, the image can only be scaled from 0 upwards
	if (sX > 0 && sY > 0)
	{		
		m1 = (m1 / axisScale.x ) * sX;
		m2 = (m2 / axisScale.x ) * sX;
		
		m4 = (m4 / axisScale.y ) * sY;
		m5 = (m5 / axisScale.y ) * sY;
	}
	
}

void Mat3::SetScale( Vec2 scale )
{
	Vec2 axisScale = GetScale();

	//Ff the scale is negative the image will reverse
	//and flicker between upright and upside down.
	//To combat this, the image can only be scaled from 0 upwards
	if( axisScale.x + scale.x > 0 )
	{
		m1 = (m1 / axisScale.x ) * scale.x;
		m2 = (m2 / axisScale.x ) * scale.x;
	}

	if( axisScale.y + scale.y > 0 )
	{
		m4 = (m4 / axisScale.y ) * scale.y;
		m5 = (m5 / axisScale.y ) * scale.y;
	}
	
}

void Mat3::AddScale(float sX, float sY)
{
	Vec2 axisScale = GetScale();

	if( axisScale.x + sX > 0 )
	{
		m1 = (m1 / axisScale.x ) * ( axisScale.x + sX );
		m2 = (m2 / axisScale.x ) * ( axisScale.x + sX );
	}

	if( axisScale.y + sY > 0 )
	{
		m4 = (m4 / axisScale.y ) * ( axisScale.y + sY );
		m5 = (m5 / axisScale.y ) * ( axisScale.y + sY );
	}

}

void Mat3::AddScale(Vec2 scale)
{
	Vec2 axisScale = GetScale();

	if( axisScale.x + scale.x > 0 )
	{
		m1 = (m1 / axisScale.x ) * ( axisScale.x + scale.x );
		m2 = (m2 / axisScale.x ) * ( axisScale.x + scale.x );
	}

	if( axisScale.y + scale.y > 0 )
	{
		m4 = (m4 / axisScale.y ) * ( axisScale.y + scale.y );
		m5 = (m5 / axisScale.y ) * ( axisScale.y + scale.y );
	}

}


Vec2 Mat3::GetScale() const
{
	return Vec2( GetRightScale(), GetUpScale() );
}

float Mat3::GetUpScale() const
{
	Vec2 yAxis(m4, m5);
	return yAxis.Length();
}

float Mat3::GetRightScale() const
{
	Vec2 xAxis(m1, m2);
	return xAxis.Length();
}

Mat3 Mat3::operator * (const Mat3 &rhs) const
{
	
	Mat3 intermediateMatrix;
	
	intermediateMatrix.m1 = (m1 * rhs.m1) + (m2 * rhs.m4) + (m3 * rhs.m7); 	   //m1
	intermediateMatrix.m2 = (m1 * rhs.m2) + (m2 * rhs.m5) + (m3 * rhs.m8);	   //m2
	intermediateMatrix.m3 = (m1 * rhs.m3) + (m2 * rhs.m6) + (m3 * rhs.m9);	   //m3
	intermediateMatrix.m4 = (m4 * rhs.m1) + (m5 * rhs.m4) + (m6 * rhs.m7);	   //m4
	intermediateMatrix.m5 = (m4 * rhs.m2) + (m5 * rhs.m5) + (m6 * rhs.m8);	   //m5
	intermediateMatrix.m6 = (m4 * rhs.m3) + (m5 * rhs.m6) + (m6 * rhs.m9);	   //m6
	intermediateMatrix.m7 = (m7 * rhs.m1) + (m8 * rhs.m4) + (m9 * rhs.m7); 	   //m7
	intermediateMatrix.m8 = (m7 * rhs.m2) + (m8 * rhs.m5) + (m9 * rhs.m8);	   //m8
	intermediateMatrix.m9 = (m7 * rhs.m3) + (m8 * rhs.m6) + (m9 * rhs.m9);	   //m9

	return intermediateMatrix;

}

Mat3& Mat3::operator *=(const Mat3 &rhs)
{
	return *this * *this *rhs;
}

Vec2 Mat3::operator * (const Vec2 &rhs) const
{
	return Vec2( (rhs.x * m1) + (rhs.y * m4) + m7, (rhs.x * m2) + (rhs.y * m5) + m8);
}

bool Mat3::operator ==( const Mat3 &rhs) const
{
	if( m1 == rhs.m1 && m2 == rhs.m2 && m3 == rhs.m3 &&
		m4 == rhs.m4 && m5 == rhs.m5 && m6 == rhs.m6 &&
		m7 == rhs.m7 && m8 == rhs.m8 && m9 == rhs.m9 )
	{
		return true;
	}

	else return false;
}

bool Mat3::operator !=( const Mat3 &rhs) const
{	
	if( m1 == rhs.m1 && m2 == rhs.m2 && m3 == rhs.m3 &&
		m4 == rhs.m4 && m5 == rhs.m5 && m6 == rhs.m6 &&
		m7 == rhs.m7 && m8 == rhs.m8 && m9 == rhs.m9 )
	{
		return false;
	}

	else return true;
}

