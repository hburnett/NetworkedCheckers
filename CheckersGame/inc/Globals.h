/*--------------------------------------------------------------------
Author: Heath Burnett

Description: Global variables and functions, only used in extreme cases
---------------------------------------------------------------------*/


#ifndef GLOBAL_H 
#define GLOBAL_H

class InputManager;

class Vec2;
 
// extern tells the compiler this variable is declared elsewhere
extern InputManager g_inputManager;

float LinearInterpolation( float time, float start, float end );
Vec2 LinearInterpolation( float time, Vec2 start, Vec2 end );

float MinimumValue( float a, float b );
Vec2 MinimumValue( Vec2 a, Vec2 b) ;

float MaximumValue( float a, float b );
Vec2 MaximumValue( Vec2 a, Vec2 b) ;

#endif