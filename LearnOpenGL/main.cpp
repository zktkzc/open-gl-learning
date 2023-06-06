#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

#pragma region 模型数据
// 顶点数组
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// 多个立方体位置向量
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

#pragma region 创建摄像机
Camera camera(glm::vec3(0, 0, 3.0f), 15.0f, 180.0f, glm::vec3(0, 1.0f, 0)); // 创建一个摄像机
#pragma endregion

#pragma region 处理键盘和鼠标输入
float lastX; // 鼠标上一帧X位置
float lastY; // 鼠标上一帧Y位置
bool firstMouse = false; // 是否是第一次鼠标进入窗口


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // 如果按下Esc键
	{
		// 设定WindowShouldClose属性为true从而关闭GLFW
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.speedZ = 1.0f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.speedZ = -1.0f;
	else
		camera.speedZ = 0;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.speedX = 1.0f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.speedX = -1.0f;
	else
		camera.speedX = 0;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.speedY = -1.0f;
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.speedY = 1.0f;
	else
		camera.speedY = 0;
}

// 鼠标移动回调函数
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse) // 如果是第一次鼠标进入窗口, 则跳过第一次，防止deltaX和deltaY差值过大
	{
		lastX = xPos; // 更新鼠标上一帧X位置
		lastY = yPos; // 更新鼠标上一帧Y位置
		firstMouse = false; // 设定为false
	}

	float deltaX, deltaY; // 鼠标位置变化量
	deltaX = xPos - lastX; // 计算鼠标X位置变化量
	deltaY = yPos - lastY; // 计算鼠标Y位置变化量

	lastX = xPos; // 更新鼠标上一帧X位置
	lastY = yPos; // 更新鼠标上一帧Y位置

	camera.ProcessMouseMovement(deltaX, deltaY); // 处理鼠标移动
}
#pragma endregion

unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot)
{
	unsigned int TexBuffer; // 纹理缓冲区对象
	glGenTextures(1, &TexBuffer); // 生成纹理
	glActiveTexture(GL_TEXTURE0 + textureSlot); // 激活纹理单元
	glBindTexture(GL_TEXTURE_2D, TexBuffer); // 绑定纹理
	// 设置纹理环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // 设置S轴环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // 设置T轴环绕方式
	// 设置纹理过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 设置缩小过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 设置放大过滤方式


	// 加载并生成纹理
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // 翻转图片
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0); // 加载图片
	if (data)
	{
		// 生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data); // 生成纹理
		glGenerateMipmap(GL_TEXTURE_2D); // 为当前绑定的纹理自动生成所有需要的多级渐远纹理
	}
	else
	{
		printf("Failed to load texture!");
	}
	stbi_image_free(data); // 释放图像的内存
	return TexBuffer;
}

int main()
{
#pragma region 初始化GLFW，配置GLFW，创建窗口
	// 初始化GLFW
	glfwInit();
	// 配置GLFW，使用的版本为3.3，核心模式
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式

	// 创建glfw窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Create GLFW window failed!");
		glfwTerminate(); // 终止GLFW
		return -1;
	}

	glfwMakeContextCurrent(window); // 设置当前上下文
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏光标
	glfwSetCursorPosCallback(window, mouse_callback); // 鼠标移动回调函数

	// 初始化glew
	glewExperimental = true; // 让glew获取所有拓展函数

	if (glewInit() != GLEW_OK) // 初始化glew失败
	{
		printf("Init GLEW failed!");
		glfwTerminate(); // 终止GLFW
		return -1;
	}
	// 设置视窗位置、大小
	glViewport(0, 0, 800, 600);

	glEnable(GL_DEPTH_TEST); // 启用深度测试
#pragma endregion

#pragma region 创建着色器程序
	Shader* myShader = new Shader("vertexShaderSource.vert", "fragmentShaderSource.frag");
#pragma endregion

#pragma region 初始化顶点数据，绑定VAO和VBO
	// 生成一个顶点数组对象(Vertex Array Object, VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// 绑定VAO
	glBindVertexArray(VAO);

	// 生成一个顶点缓冲对象(Vertex Buffer Objects, VBO)
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// 把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 把用户定义的数据复制到当前绑定缓冲的函数
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 设置顶点属性指针
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0); // 解析顶点数据
	glEnableVertexAttribArray(6); // 启用顶点属性
	glVertexAttribPointer(9, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float))); // 解析纹理法线数据
	glEnableVertexAttribArray(9); // 启用顶点属性

#pragma endregion

#pragma region 加载纹理
	// 纹理
	unsigned int TexBufferA;
	TexBufferA = LoadImageToGPU("container.jpg", GL_RGB, GL_RGB, 0);

	unsigned int TexBufferB;
	TexBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 3);
#pragma endregion

#pragma region 准备模型矩阵，观察矩阵，投影矩阵
	glm::mat4 modelMat; // 模型矩阵
	glm::mat4 viewMat; // 观察矩阵
	glm::mat4 projectionMat; // 投影矩阵
	projectionMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // 透视投影
#pragma endregion

#pragma region 渲染循环
	while (!glfwWindowShouldClose(window)) // 每次循环的开始前检查一次GLFW是否被要求退出
	{
		processInput(window); // 处理输入

		// 清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearColor(0, 0, 0, 1.0f);
		// 清除颜色缓冲
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 同时清除深度缓冲

		viewMat = camera.GetViewMatrix(); // 获取观察矩阵

		for (int i = 0; i < 10; i++)
		{
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]); // 位移

			myShader->use(); // 使用着色器程序

			glActiveTexture(GL_TEXTURE0); // 激活纹理单元
			glBindTexture(GL_TEXTURE_2D, TexBufferA); // 绑定纹理
			glActiveTexture(GL_TEXTURE3); // 激活纹理单元
			glBindTexture(GL_TEXTURE_2D, TexBufferB); // 绑定纹理

			// glUniform1i(glGetUniformLocation(myShader->id, "ourTexture"), 0); // 手动设置纹理单元
			// glUniform1i(glGetUniformLocation(myShader->id, "ourFace"), 3); // 手动设置纹理单元
			glUniformMatrix4fv(glGetUniformLocation(myShader->id, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat)); // 手动设置纹理单元
			glUniformMatrix4fv(glGetUniformLocation(myShader->id, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat)); // 手动设置纹理单元
			glUniformMatrix4fv(glGetUniformLocation(myShader->id, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat)); // 手动设置纹理单元
			glUniform3f(glGetUniformLocation(myShader->id, "objColor"), 1.0f, 0.5f, 0.3f); // 手动设置纹理单元
			glUniform3f(glGetUniformLocation(myShader->id, "ambientColor"), 0.2f, 0.1f, 0.0f); // 手动设置纹理单元
			glUniform3f(glGetUniformLocation(myShader->id, "lightPos"), 10.0f, 10.0f, -5.0f); // 手动设置纹理单元
			glUniform3f(glGetUniformLocation(myShader->id, "lightColor"), 1.0f, 1.0f, 1.0f); // 手动设置纹理单元
			glUniform3f(glGetUniformLocation(myShader->id, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z); // 手动设置纹理单元

			glUniform3f(glGetUniformLocation(myShader->id, "material.ambient"), 1.0f, 1.0f, 1.0f); // 手动设置纹理单元
			glUniform3f(glGetUniformLocation(myShader->id, "material.diffuse"), 0, 0, 1.0f); // 手动设置纹理单元
			glUniform3f(glGetUniformLocation(myShader->id, "material.specular"), 0, 1.0f, 0); // 手动设置纹理单元
			glUniform1f(glGetUniformLocation(myShader->id, "material.shininess"), 64.0f); // 手动设置纹理单元

			glBindVertexArray(VAO); // 绑定VAO

			glDrawArrays(GL_TRIANGLES, 0, 36); // 绘制立方体, 36个顶点
		}

		// 交换颜色缓冲
		glfwSwapBuffers(window);
		// 检查有没有触发什么事件（比如键盘输入、鼠标移动等），然后调用对应的回调函数（可以通过回调方法手动设置）
		glfwPollEvents();
		camera.UpdateCameraPosition(); // 更新摄像机位置
	}
#pragma endregion

	// 释放GLFW分配的内存
	glfwTerminate();

	return 0;
}