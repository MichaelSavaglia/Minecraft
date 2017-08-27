#version 450 core

out vec3 color;

in vec2 textured;

uniform sampler2D myTextureSampler;

void main()
{
	color = texture(myTextureSampler,textured).rgb;
	//color = vec3(1.0, 0.0, 1.0);
}