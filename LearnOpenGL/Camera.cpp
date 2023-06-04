#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	position = position; // 摄像机位置向量
	Forward = glm::normalize(target - position); // 转化为单位向量，即方向向量，由目标点和摄像机位置向量相减得到
	Right = glm::normalize(glm::cross(Forward, worldUp)); // 右向量,由世界坐标系的上向量和前向量叉乘得到
	Up = glm::normalize(glm::cross(Forward, Right)); // 上向量，由右向量和前向量叉乘得到
	WorldUp = worldUp; // 世界坐标系的上向量
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp)
{
	Position = position;
	WorldUp = worldUp;
	Pitch = pitch;
	Yaw = yaw;
	Forward.x = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw)); // 由俯仰角和偏航角计算前向量的x分量
	Forward.y = glm::sin(glm::radians(Pitch)); // 由俯仰角计算前向量的y分量
	Forward.z = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw)); // 由俯仰角和偏航角计算前向量的z分量
	Right = glm::normalize(glm::cross(Forward, worldUp)); // 右向量,由世界坐标系的上向量和前向量叉乘得到
	Up = glm::normalize(glm::cross(Forward, Right)); // 上向量，由右向量和前向量叉乘得到
}

Camera::~Camera()
{
}

/// <summary>
/// 获取观察矩阵
/// </summary>
/// <returns></returns>
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, WorldUp); // 由摄像机位置向量，目标点向量，世界坐标系的上向量得到观察矩阵
}

// 处理鼠标移动
void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
	Pitch -= deltaY * SenseX; // 俯仰角
	Yaw -= deltaX * SenseY; // 偏航角
	UpdateCameraVectors(); // 更新摄像机位置向量
}

// 更新摄像机位置向量
void Camera::UpdateCameraPosition()
{
	Position += Forward * speedZ * 0.1f; // 摄像机位置向量加上前向量乘以速度
}

// 由于摄像机的位置向量和目标点向量是一一对应的，所以只要更新摄像机位置向量就可以了
void Camera::UpdateCameraVectors()
{
	Forward.x = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw)); // 由俯仰角和偏航角计算前向量的x分量
	Forward.y = glm::sin(glm::radians(Pitch)); // 由俯仰角计算前向量的y分量
	Forward.z = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw)); // 由俯仰角和偏航角计算前向量的z分量
	Right = glm::normalize(glm::cross(Forward, WorldUp)); // 右向量,由世界坐标系的上向量和前向量叉乘得到
	Up = glm::normalize(glm::cross(Forward, Right)); // 上向量，由右向量和前向量叉乘得到
}
