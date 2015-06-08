#include "Camera.h"
#include "Mat3.h"
#include "Vec2.h"

Camera::Camera()
{
	cameraMatrix.SetTranslation(0, 0);
	cameraMatrix.SetScale(1, 1);
}

Camera::Camera( float xPos, float yPos, float xScale, float yScale )
{
	cameraMatrix.SetTranslation(xPos, yPos);
	cameraMatrix.SetScale(xScale, yScale);
}

Camera::Camera( Vec2 pos, Vec2 scale )
{
	cameraMatrix.SetTranslation(pos);
	cameraMatrix.SetScale(scale);
}

//Remember that this vector should be the opposite to the players movement vector.
//This function adds the vector to the cameras current position, it does not set the position.
void Camera::MoveCamera( Vec2 movementVector )
{
	cameraMatrix.AddTranslation(movementVector);
}

//Sets the camera's current position, (0,0) is default
void Camera::SetCameraPosition( Vec2 position )
{
	cameraMatrix.SetTranslation(position * -1);
}

//This function adds the vector to the cameras current scale, it does not set the scale.
void Camera::ZoomCamera( Vec2 zoomVector )
{
	cameraMatrix.AddScale(zoomVector);
}

//Sets the cameras current zoom level, (1,1) is default.
void Camera::SetCameraZoom( Vec2 zoom )
{
	cameraMatrix.SetScale(zoom);
}