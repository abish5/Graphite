#version 410
		 
layout(location = 0) out vec4 color;
			
uniform vec3 u_Color;
			
in vec3 v_Position;

void main()
{ 
	color = vec4(u_Color, 1.0);
}