#include "InputManager.h"
#include "Vec2.h"
#include <math.h>

InputManager g_inputManager = InputManager();

class Vec2;

float LinearInterpolation( float time, float start, float end )
{
	return (start * (1 - time)) + (end * time);
}

Vec2 LinearInterpolation( float time, Vec2 start, Vec2 end )
{
	return (start * (1 - time)) + (end * time);
}

// Uses absolute values
// Eg: 5 and -100. 5 is the minimum.
float MinimumValue( float a, float b ) 
{
	float c = abs(a);
	float d = abs(b);

	if( c < d ) 
	{ 
		return a;
	} 

	else return b; 
}

// Uses absolute values
// Eg: 5 and -100. 5 is the minimum.
Vec2 MinimumValue( Vec2 a, Vec2 b ) 
{ 
	Vec2 c = Vec2( abs(a.x),abs(a.y));
	Vec2 d = Vec2( abs(b.x),abs(b.y));

	float aLen = c.Length();
	float bLen = d.Length();
	
	
	if( aLen < bLen ) 
	{ 
		return a;
	} 

	else return b;
}

// Uses absolute values
// Eg: 5 and -100. -100 is the maximum.
float MaximumValue( float a, float b ) 
{
	float c = abs(a);
	float d = abs(b);

	if( c < d ) 
	{ 
		return b;
	} 

	else return a; 
}

// Uses absolute values
// Eg: 5 and -100. -100 is the maximum.
Vec2 MaximumValue( Vec2 a, Vec2 b ) 
{ 
	Vec2 c = Vec2( abs(a.x),abs(a.y));
	Vec2 d = Vec2( abs(b.x),abs(b.y));

	float aLen = c.Length();
	float bLen = d.Length();
	
	if( aLen < bLen ) 
	{ 
		return b;
	} 

	else return a;
}