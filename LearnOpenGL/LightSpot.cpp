#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color)
	: position(_position), angles(_angles), color(_color)
{
	UpdateDirection();
}

void LightSpot::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f); // ָ��z��������
	direction = glm::rotateZ(direction, angles.z); // ��z����ת
	direction = glm::rotateX(direction, angles.x); // ��x����ת
	direction = glm::rotateY(direction, angles.y); // ��y����ת
	direction = -1.0f * direction; // ����
}
