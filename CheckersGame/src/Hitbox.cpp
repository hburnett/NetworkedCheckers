#include "Hitbox.h"

// Default constructor
// Sets all values to 0
RectangleHitbox::RectangleHitbox()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	halfWidth = 0;
	halfHeight = 0;
}

// Constructor
RectangleHitbox::RectangleHitbox(float xPos, float yPos, float w, float h)
{
	x = xPos;
	y = yPos;
	width = w;
	height = h;
	halfWidth = width / 2;
	halfHeight = height / 2;
}

// Constructor
RectangleHitbox::RectangleHitbox(Vec2 pos, float w, float h)
{
	x = pos.x;
	y = pos.y;
	width = w;
	height = h;
	halfWidth = width / 2;
	halfHeight = height / 2;
}

// Constructor
RectangleHitbox::RectangleHitbox(float xPos, float yPos, Vec2 dim)
{
	x = xPos;
	y = yPos;
	width = dim.x;
	height = dim.y;
	halfWidth = width / 2;
	halfHeight = height / 2;
}

// Constructor
RectangleHitbox::RectangleHitbox(Vec2 pos, Vec2 dim)
{
	x = pos.x;
	y = pos.y;
	width = dim.x;
	height = dim.y;
	halfWidth = width / 2;
	halfHeight = height / 2;
}

// Checks if the rectangles are intersecting or not
bool RectangleHitbox::Intersects(RectangleHitbox rect)
{	
	//if( (((x - halfWidth <= rect.x + rect.halfWidth) && (x - halfWidth >= rect.x - rect.halfWidth))		
	//	||
	//	((x + halfWidth <= rect.x + rect.halfWidth) && (x + halfWidth >= rect.x - halfWidth)))
	//	&&
	//	(((y + halfHeight <= rect.y + rect.halfHeight) && (y + halfHeight >= rect.y - rect.halfHeight))
	//	||
	//	((y - halfHeight <= rect.y + rect.halfHeight) && ( y - halfHeight >= rect.y - rect.halfHeight))
	//	||
	//	(y == rect.y)
	//	||
	//	(y - halfHeight <= rect.y - rect.halfHeight) && (y + halfHeight >= rect.y + rect.halfHeight)))

	float left		= Left();
	float right		= Right();
	float top		= Top();
	float bottom	= Bottom();

	float rLeft		= rect.Left();
	float rRight	= rect.Right();
	float rTop		= rect.Top();
	float rBottom	= rect.Bottom();
	
	
	if (((rLeft >= left && rLeft <= right) || (rRight >= left && rRight <= right)) 
		&&
		((rTop >= bottom && rTop <= top) || (rBottom >= bottom && rBottom <= top)))
	{
		return true;
	}

	else if (((left >= rLeft && left <= rRight) || (right >= rLeft && right <= rRight)) 
		&&
		((top >= rBottom && top <= rTop) || (bottom >= rBottom && bottom <= rTop)))
	{
		return true;
	}

	else return false;

}

// Checks if the point is within the rectangle
bool RectangleHitbox::Contains(Vec2 point)
{
	if( (point.x >= Left() && point.x <= Right()) 
		&&
		(point.y >= Bottom() && point.y <= Top()))
	{
		return true;
	}

	else return false;

}