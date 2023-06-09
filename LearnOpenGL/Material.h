#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
	Material(Shader* _shader, unsigned int _diffuse, unsigned int _specular, glm::vec3 _ambient, float _shininess);
	~Material() = default;

public:
	Shader* shader;
	unsigned int diffuse; // 漫反射
	unsigned int specular; // 镜面反射
	glm::vec3 ambient; // 环境光
	float shininess; // 镜面反射高光度
};

