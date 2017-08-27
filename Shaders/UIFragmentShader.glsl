#version 450 core

in vec2 UV;

out vec4 color;

uniform sampler2D myTextureSampler;

void main()
{
	vec4 texColor = texture( myTextureSampler, UV);

	if(texColor.a < 0.1)
	{
		discard;
	}

	color = texColor.rgba;
}