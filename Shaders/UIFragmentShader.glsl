#version 450 core

in vec2 UV;

// Ouput data
out vec3 color;

uniform sampler2D myTextureSampler;

void main()
{
	color = texture( myTextureSampler, UV ).rgb;
}