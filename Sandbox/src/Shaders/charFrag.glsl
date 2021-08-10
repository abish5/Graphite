#version 410

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D image;
uniform vec3 u_SpriteColor;

void main()
{ 
	color = texture(image, v_TexCoord);
	if (color.rgb == vec3(0,0,0)) discard;
}