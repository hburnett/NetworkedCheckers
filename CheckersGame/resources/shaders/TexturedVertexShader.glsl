#version 400

in vec4 vPosition;
in vec4 vColour;
in vec2 vUV;

uniform mat4 projection;

out vec4 colour;
out vec2 UV;

void main()
{
	colour	= vColour;
	UV 		= vUV;

	gl_Position = projection * vPosition;
}