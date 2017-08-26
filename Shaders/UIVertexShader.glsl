#version 450 core

layout(location = 3) in vec2 vertPos;
layout(location = 4) in vec2 vertUV;

out vec2 UV;

void main()
{
	vec2 vertHomoPos = vertPos - vec2(640, 360);
	vertHomoPos /= vec2(640, 360);
	gl_Position = vec4(vertHomoPos, 0, 1);

	UV = vertUV;
}