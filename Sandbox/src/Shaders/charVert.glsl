#version 410
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;
//uniform mat4 u_Transform;

void main()
{
	v_TexCoord = vec2(a_TexCoord.x, a_TexCoord.y);
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);
}