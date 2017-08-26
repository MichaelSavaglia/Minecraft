#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 instance_position;

uniform mat4 MVP;

void main()
{
	vec4 pos = vec4(position + instance_position, 1);
	gl_Position = MVP * pos;
}