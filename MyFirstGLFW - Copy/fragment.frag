#version 330

layout (location = 0) out vec4 color;
varying vec2 vPos;

void main()
{
	color = vec4(0.0, 0.0, 1.0, 1.0);

	
	float dot = dot(normalize(vPos), vec2(1.0, 0.0));
	
		color = vec4(1.0, 1.0, 1.0, 1.0);

		if(dot>0.707107 && vPos.y>0) 
		{
			color = vec4(1.0, 0.0, 0.0, 1.0);
		}

		else if(dot>0 && dot<0.707107 && vPos.y>0) 
		{
			color = vec4(0.0, 1.0, 0.0, 1.0);
		}

		else if(dot<0 && dot>-0.707107 && vPos.y>0) 
		{
			color = vec4(0.0, 0.0, 1.0, 1.0);
		}

		else if(dot>-1 && dot<-0.707107 && vPos.y>0) 
		{
			color = vec4(0.160, 1, 0.921, 1.0);
		}

		else if(dot<-0.707107 && vPos.y<0) 
		{
			color = vec4(1, 0.925, 0.160, 1.0);
		}

		else if(dot<0 && dot>-0.707107 && vPos.y<0) 
		{
			color = vec4(0.698, 0.160, 1, 1.0);
		}

		else if(dot>0 && dot<0.707107 && vPos.y<0) 
		{
			color = vec4(1, 0.160, 0.941, 1.0);
		}

		else if(dot>0.707107 && vPos.y<0) 
		{
			color = vec4(0.847, 0.619, 0.231, 1.0);
		}
	
}
