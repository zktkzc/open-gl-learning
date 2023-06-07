#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color)
	: position(_position), angles(_angles), color(_color)
{
	UpdateDirection();
}

void LightSpot::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f); // 指向z轴正方向
	direction = glm::rotateZ(direction, angles.z); // 绕z轴旋转
	direction = glm::rotateX(direction, angles.x); // 绕x轴旋转
	direction = glm::rotateY(direction, angles.y); // 绕y轴旋转
	direction = -1.0f * direction; // 反向
}
