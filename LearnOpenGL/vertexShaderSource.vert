#version 330 core
layout(location = 6) in vec3 aPos;
layout(location = 9) in vec3 aNormal;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

out vec3 FragPos;
out vec3 Normal;

void main()
{
	gl_Position = projectionMat * viewMat * modelMat * vec4(aPos.xyz, 1.0f);
	Normal = mat3(modelMat) * aNormal;
};