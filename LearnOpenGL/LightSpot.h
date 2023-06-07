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
	glm::vec3 position; // λ��
	glm::vec3 angles; // ŷ����
	glm::vec3 direction; // ����
	glm::vec3 color; // ��ɫ
	float cosPhyInner = 0.9f; // ��׶���ڽ�����ֵ������Ž�
	float cosPhyOuter = 0.85f; // ��׶���������ֵ����С�Ž�
};

