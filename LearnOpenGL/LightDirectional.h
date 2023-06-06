#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightDirectional
{
public:
	LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightDirectional() = default;
	void UpdateDirection();

public:
	glm::vec3 position; // 位置
	glm::vec3 angles; // 欧拉角
	glm::vec3 direction; // 方向
	glm::vec3 color; // 颜色
};

