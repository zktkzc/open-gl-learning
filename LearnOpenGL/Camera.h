#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);
	~Camera();
	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float deltaX, float deltaY);
	void UpdateCameraPosition();

public:
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Pitch; // 俯仰角
	float Yaw; // 偏航角
	float SenseX = 0.01f; // 鼠标灵敏度
	float SenseY = 0.01f; // 鼠标灵敏度
	float speedX = 0; // 摄像机左右移动速度
	float speedY = 0; // 摄像机上下移动速度
	float speedZ = 0; // 摄像机前后移动速度

private:
	void UpdateCameraVectors();
};