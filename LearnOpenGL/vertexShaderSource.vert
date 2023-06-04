#version 330 core
layout(location = 6) in vec3 aPos;
layout(location = 7) in vec3 aColor;
layout(location = 8) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 TexCoord;

// uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main()
{
	gl_Position = projectionMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0f);
	TexCoord = aTexCoord;
};