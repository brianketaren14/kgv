#version 330

uniform vec4 color1;
uniform vec4 color2;

layout (location = 0) out vec4 color;
varying vec2 vPos;
void main()
{
	if(vPos.y<0)
	{
		color = color1;
	}
	else 
	{
		color = color2;
	}
}