#version 410

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec4 v_Color;	
out vec2 v_TexCoord;

void main()
{
	v_Color = a_Color;
	v_TexCoord = vec2(a_TexCoord.x, a_TexCoord.y);
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}