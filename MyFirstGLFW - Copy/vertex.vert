#version 330

uniform float scale;
layout (location = 0) in vec2 pos;
varying vec2 vPos;
void main()
{
	
	gl_Position = vec4(pos.xy*scale, 0.0, 1.0);
	vPos = pos.xy;
}