#version 410

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D texture1;

void main()
{ 
	//color = vec4(v_Position * 0.5 + 0.5, 1.0);
	//color = v_Color;
	color = texture(texture1, TexCoord);

}