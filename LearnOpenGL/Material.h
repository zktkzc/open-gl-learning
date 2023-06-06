#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
	Material(Shader* _shader, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _ambient, float _shininess);
	~Material() = default;

public:
	Shader* shader;
	glm::vec3 diffuse; // ������
	glm::vec3 specular; // ���淴��
	glm::vec3 ambient; // ������
	float shininess; // ���淴��߹��
};

