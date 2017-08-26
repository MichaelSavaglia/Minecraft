#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 instance_position;
layout(location = 2) in float section_position;

uniform mat4 MVP;

void main()
{
	vec4 pos = vec4(position + instance_position, 1);
	pos.y += section_position * 16.0;
	gl_Position = MVP * pos;
}