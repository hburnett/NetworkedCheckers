/*--------------------------------------------------------------------
Author: Heath Burnett

Description: Hitbox classes. Will contain rectangles and circles.
---------------------------------------------------------------------*/


#ifndef HITBOX_H
#define HITBOX_H
#include "Vec2.h"

class Vec2;

class RectangleHitbox
{

public:	

	RectangleHitbox();

	RectangleHitbox(float xPos, float yPos, float w, float h);

	RectangleHitbox(Vec2 pos, float w, float h);

	RectangleHitbox(float xPos, float yPos, Vec2 dim);

	RectangleHitbox(Vec2 pos, Vec2 dim);

	bool Intersects(RectangleHitbox rect);

	bool Contains( Vec2 point );

	void SetPosition( float xPos, float yPos )
	{	x = xPos;		y = yPos;	}

	void SetPosition( Vec2 pos )
	{	x = pos.x;		y = pos.y;	}

	Vec2 GetPosition()
	{	return Vec2(x,y);	}
	
	void SetDimensions( float w, float h )
	{	width = w;		height = h;	}

	void SetDimensions( Vec2 dim )
	{	width = dim.x;	height = dim.y;	}
	
	Vec2 GetDimensions()
	{	return Vec2(width, height);	}

	// Returns the y value of the top side of the rectangle.
	float Top()
	{	return y + height / 2;	}

	// Returns the y value of the bottom side of the rectangle.
	float Bottom()
	{	return y - height / 2;	}

	// Returns the x value of the right side of the rectangle.
	float Right()
	{	return x + width / 2; }

	// Returns the x value of the left side of the rectangle.
	float Left()
	{	return x - width / 2; }


	float		x;
	float		y;
	float		width;
	float		height;
	float		halfWidth;
	float		halfHeight;
	
};
#endif