#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightPoint
{
public:
	LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint() = default;

public:
	glm::vec3 position; // 位置
	glm::vec3 angles; // 欧拉角
	glm::vec3 direction; // 方向
	glm::vec3 color; // 颜色
	float constant; // 常数项
	float linear; // 一次项衰减值
	float quadratic; // 二次项衰减值
};

