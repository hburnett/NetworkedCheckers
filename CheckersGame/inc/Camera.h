/*---------------------------------------------------------------------------------------------
Author: Heath Burnett

Description: Camera class, handles 
movement and zoom.
			 Does not handle rotation. Feature will be put in place when needed.
---------------------------------------------------------------------------------------------*/
#ifndef CAMERA_H 
#define CAMERA_H

#include "Mat3.h"

class Vec2;
class Mat3;

class Camera
{	

public:
	
	//Default constructor
	//Initialises translation to 0 and zoom levels to 1
	Camera();

	//Initiliases translation and zoom levels to those passed in
	Camera( float xPos, float yPos, float xScale, float yScale );

	//Initiliases translation and zoom levels to those passed in
	Camera( Vec2 pos, Vec2 scale );
	
	//Remember that this vector should be the opposite to the players movement vector.
	//Adds the vector to the cameras current position, it does not set the position.
	void	MoveCamera( Vec2 movementVector );
	
	//Sets the camera's current position, (0,0) is default
	void	SetCameraPosition( Vec2 position );

	//Adds the vector to the cameras current zoom, does not set the zoom.
	void	ZoomCamera( Vec2 zoomVector );

	//Sets the cameras current zoom level, (1,1) is default.
	void	SetCameraZoom( Vec2 zoom );

	Mat3	cameraMatrix;

};

#endif