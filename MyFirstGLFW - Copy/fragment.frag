#version 330

uniform vec4 color1; 
uniform vec4 color2; 
uniform vec4 color3; 
uniform vec4 color4; 
uniform vec4 color5; 
uniform vec4 color6; 
uniform vec4 color7; 
uniform vec4 color8;

layout (location = 0) out vec4 color;
varying vec2 vPos;

void main()
{
	
	float dot = dot(normalize(vPos), vec2(1.0, 0.0));

		if(dot>0.707107 && vPos.y>0 && vPos.x>0) 
		{
			color = color1;
		}

		else if(dot>0 && dot<0.707107 && vPos.y>0 && vPos.x>0) 
		{
			color = color2;
		}

		else if(dot<0 && dot>-0.707107 && vPos.y>0 && vPos.x<0) 
		{
			color = color3;
		}

		else if(dot>-1 && dot<-0.707107 && vPos.y>0 && vPos.x<0) 
		{
			color = color4;
		}

		else if(dot<-0.707107 && vPos.y<0 && vPos.x<0) 
		{
			color = color5;
		}

		else if(dot<0 && dot>-0.707107 && vPos.y<0 && vPos.x<0) 
		{
			color = color6;
		}

		else if(dot>0 && dot<0.707107 && vPos.y<0 && vPos.x>0) 
		{
			color = color7;
		}

		else if(dot>0.707107 && vPos.y<0 && vPos.x>0) 
		{
			color = color8;
		}
	
}
