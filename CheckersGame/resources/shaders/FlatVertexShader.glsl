#version 400

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColour;

uniform mat4 projection;

out vec4 colour;
//out vec4 position;

void main()
{
	//position		= projection * vPosition;
	colour			= vColour;
	gl_Position 	= projection * vPosition;
	
}