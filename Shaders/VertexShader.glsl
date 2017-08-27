#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in ivec3 instance_position;
layout(location = 2) in vec2 textureData;

uniform mat4 MVP;

out vec2 textured;

void main()
{
	vec4 pos = vec4(position + instance_position, 1);
	textured = textureData;
	gl_Position = MVP * pos;
}