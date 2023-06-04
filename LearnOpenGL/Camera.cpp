#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	position = position; // �����λ������
	Forward = glm::normalize(target - position); // ת��Ϊ��λ��������������������Ŀ���������λ����������õ�
	Right = glm::normalize(glm::cross(Forward, worldUp)); // ������,����������ϵ����������ǰ������˵õ�
	Up = glm::normalize(glm::cross(Forward, Right)); // ������������������ǰ������˵õ�
	WorldUp = worldUp; // ��������ϵ��������
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp)
{
	Position = position;
	WorldUp = worldUp;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw)); // �ɸ����Ǻ�ƫ���Ǽ���ǰ������x����
	Forward.y = glm::sin(glm::radians(Pitch)); // �ɸ����Ǽ���ǰ������y����
	Forward.z = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw)); // �ɸ����Ǻ�ƫ���Ǽ���ǰ������z����
	Right = glm::normalize(glm::cross(Forward, worldUp)); // ������,����������ϵ����������ǰ������˵õ�
	Up = glm::normalize(glm::cross(Forward, Right)); // ������������������ǰ������˵õ�
}

Camera::~Camera()
{
}

/// <summary>
/// ��ȡ�۲����
/// </summary>
/// <returns></returns>
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, WorldUp); // �������λ��������Ŀ�����������������ϵ���������õ��۲����
}

// ��������ƶ�
void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch -= deltaY * SenseX; // ������
	Yaw -= deltaX * SenseY; // ƫ����
	UpdateCameraVectors(); // ���������λ������
}

// ���������λ������
void Camera::UpdateCameraPosition()
{
	Position += Forward * speedZ * 0.1f; // �����λ����������ǰ���������ٶ�
}

// �����������λ��������Ŀ���������һһ��Ӧ�ģ�����ֻҪ���������λ�������Ϳ�����
void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw)); // �ɸ����Ǻ�ƫ���Ǽ���ǰ������x����
	Forward.y = glm::sin(glm::radians(Pitch)); // �ɸ����Ǽ���ǰ������y����
	Forward.z = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw)); // �ɸ����Ǻ�ƫ���Ǽ���ǰ������z����
	Right = glm::normalize(glm::cross(Forward, WorldUp)); // ������,����������ϵ����������ǰ������˵õ�
	Up = glm::normalize(glm::cross(Forward, Right)); // ������������������ǰ������˵õ�
}
