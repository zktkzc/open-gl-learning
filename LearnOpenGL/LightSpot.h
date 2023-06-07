#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightSpot
{
public:
	LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot() = default;
	void UpdateDirection();

public:
	glm::vec3 position; // 位置
	glm::vec3 angles; // 欧拉角
	glm::vec3 direction; // 方向
	glm::vec3 color; // 颜色
	float cosPhyInner = 0.9f; // 光锥的内角余弦值，最大张角
	float cosPhyOuter = 0.85f; // 光锥的外角余弦值，最小张角
};

