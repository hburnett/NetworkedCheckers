#version 400

in vec4 colour;
//in vec4 position;

out vec4 outColour;

void main()
{
	//outColour(position.x, position.y, 1, 1);
	//outColour = vec4(1, 0, 0, 1);
	outColour = colour;
}