#version 450 core

struct Material
{
	vec3 diffuse;
	vec3 specular;
    float shininess;
};

struct Light
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec3 color;

in vec2 textured;
in vec3 fragPos;
in vec3 normal;

uniform sampler2D myTextureSampler;
uniform vec3 eye;
uniform Material material;
uniform Light light;

void main()
{
	//color = texture(myTextureSampler,textured).rgb;
	//color = vec3(1.0, 0.0, 1.0);

	vec3 ambient = light.ambient * material.diffuse;
	
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * material.diffuse;
	
	vec3 viewDir = normalize(eye - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * material.specular;
	
	color = texture(myTextureSampler,textured).rgb * vec3(ambient + diffuse + specular);
}