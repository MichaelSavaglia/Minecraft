#version 450 core
in vec2 UV;
out vec3 color;
uniform sampler2D myTextureSampler;

void main()
{
	color = texture(myTextureSampler, UV).rgb;
	//color = vec3(1.0, 0.0, 1.0);
}