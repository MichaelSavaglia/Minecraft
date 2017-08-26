#version 450 core

in vec2 UV;

// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;

void main()
{
	vec4 texColor = texture( myTextureSampler, UV);

	color = texColor.rgba;
}