#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in ivec3 instance_position;
layout(location = 2) in vec2 textureData;
layout(location = 3) in vec3 vertex_normal;
layout(location = 4) in vec3 instance_texture_data;


uniform mat4 MVP;
uniform mat4 Model;
uniform mat4 View;

out vec2 textured;
out vec3 fragPos;
out vec3 normal;

void main()
{
	vec4 pos			= vec4(position + instance_position, 1);

	float numberofRows	= instance_texture_data.x;
	vec2 offset			= instance_texture_data.yz;
	textured			= (textureData / numberofRows) + offset;

	gl_Position			= MVP * pos;

	fragPos = (Model * pos).xyz;
	normal = mat3(transpose(inverse(Model))) * vertex_normal;
}