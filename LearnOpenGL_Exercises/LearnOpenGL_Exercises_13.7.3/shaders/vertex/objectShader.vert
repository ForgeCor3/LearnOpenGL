#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPosition;
out vec3 LightPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPosition;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	Normal = mat3(transpose(inverse(view * model))) * aNormal;
	FragPosition = vec3(view * model * vec4(aPos, 1.0));
	LightPosition = vec3(view * vec4(lightPosition, 1.0));
}