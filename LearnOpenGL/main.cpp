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

// ��������
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

float lastX; // �����һ֡Xλ��
float lastY; // �����һ֡Yλ��
bool firstMouse = false; // �Ƿ��ǵ�һ�������봰��

// Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0)); // ����һ�������
Camera camera(glm::vec3(0, 0, 3.0f), 15.0f, 180.0f, glm::vec3(0, 1.0f, 0)); // ����һ�������

// ��������
unsigned int indices[] = { // ��ʱ�����Ϊ����
	0, 1, 2,
	2, 3, 0
};

// ���������λ������
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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // �������Esc��
	{
		// �趨WindowShouldClose����Ϊtrue�Ӷ��ر�GLFW
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.speedZ = 1.0f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.speedZ = -1.0f;
	else
		camera.speedZ = 0;
}

// ����ƶ��ص�����
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse) // ����ǵ�һ�������봰��, ��������һ�Σ���ֹdeltaX��deltaY��ֵ����
	{
		lastX = xPos; // ���������һ֡Xλ��
		lastY = yPos; // ���������һ֡Yλ��
		firstMouse = false; // �趨Ϊfalse
	}

	float deltaX, deltaY; // ���λ�ñ仯��
	deltaX = xPos - lastX; // �������Xλ�ñ仯��
	deltaY = yPos - lastY; // �������Yλ�ñ仯��

	lastX = xPos; // ���������һ֡Xλ��
	lastY = yPos; // ���������һ֡Yλ��

	camera.ProcessMouseMovement(deltaX, deltaY); // ��������ƶ�
}

int main()
{
	// ��ʼ��GLFW
	glfwInit();
	// ����GLFW��ʹ�õİ汾Ϊ3.3������ģʽ
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // �ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ����ģʽ

	// ����glfw����
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Create GLFW window failed!");
		glfwTerminate(); // ��ֹGLFW
		return -1;
	}

	glfwMakeContextCurrent(window); // ���õ�ǰ������
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ���ع��
	glfwSetCursorPosCallback(window, mouse_callback); // ����ƶ��ص�����

	// ��ʼ��glew
	glewExperimental = true; // ��glew��ȡ������չ����

	if (glewInit() != GLEW_OK) // ��ʼ��glewʧ��
	{
		printf("Init GLEW failed!");
		glfwTerminate(); // ��ֹGLFW
		return -1;
	}
	// �����Ӵ�λ�á���С
	glViewport(0, 0, 800, 600);

	// �����޳�
	// glEnable(GL_CULL_FACE); // �������޳�
	// glCullFace(GL_BACK); // �޳�����

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // ���û���ģʽΪ�߿�ģʽ

	glEnable(GL_DEPTH_TEST); // ������Ȳ���

	Shader* myShader = new Shader("vertexShaderSource.txt", "fragmentShaderSource.txt");

	// ����һ�������������(Vertex Array Object, VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// ��VAO
	glBindVertexArray(VAO);

	// ����һ�����㻺�����(Vertex Buffer Objects, VBO)
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// ���´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���û���������ݸ��Ƶ���ǰ�󶨻���ĺ���
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO; // �����������(Element Buffer Object, EBO)
	glGenBuffers(1, &EBO); // ����һ�������������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // ���´����Ļ���󶨵�GL_ELEMENT_ARRAY_BUFFERĿ����
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // ���û���������ݸ��Ƶ���ǰ�󶨻���ĺ���

	// ���ö�������ָ��
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0); // ������������
	glEnableVertexAttribArray(6); // ���ö�������
	// glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float))); // ������ɫ����
	// glEnableVertexAttribArray(7); // ���ö�������
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float))); // ����������������
	glEnableVertexAttribArray(8); // ���ö�������

	// ����
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA); // ��������
	glActiveTexture(GL_TEXTURE0); // ��������Ԫ
	glBindTexture(GL_TEXTURE_2D, TexBufferA); // ������
	// ���������Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // ����S�ỷ�Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // ����T�ỷ�Ʒ�ʽ
	// ����������˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // ������С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // ���÷Ŵ���˷�ʽ

	// ���ز���������
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // ��תͼƬ
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0); // ����ͼƬ
	if (data)
	{
		// ��������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // ��������
		glGenerateMipmap(GL_TEXTURE_2D); // Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
	}
	else
	{
		printf("Failed to load texture!");
	}
	stbi_image_free(data); // �ͷ�ͼ����ڴ�

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB); // ��������
	glActiveTexture(GL_TEXTURE3); // ��������Ԫ
	glBindTexture(GL_TEXTURE_2D, TexBufferB); // ������

	// ���������Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // ����S�ỷ�Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); // ����T�ỷ�Ʒ�ʽ
	// ����������˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // ������С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // ���÷Ŵ���˷�ʽ

	// ���ز���������
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0); // ����ͼƬ
	if (data)
	{
		// ��������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // ��������
		glGenerateMipmap(GL_TEXTURE_2D); // Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
	}
	else
	{
		printf("Failed to load texture!");
	}
	stbi_image_free(data); // �ͷ�ͼ����ڴ�

	glm::mat4 trans; // ����һ����ά����
	// trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0)); // λ��
	// trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 0, 1.0f)); // ��ת
	// trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f)); // ����

	glm::mat4 modelMat; // ģ�;���
	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0)); // ��ת

	glm::mat4 viewMat; // �۲����
	// viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f)); // λ��
	// viewMat = camera.GetViewMatrix(); // ��ȡ�۲����

	glm::mat4 projectionMat; // ͶӰ����
	projectionMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // ͸��ͶӰ

	while (!glfwWindowShouldClose(window)) // ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
	{
		processInput(window);

		// �����ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// �����ɫ����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ͬʱ�����Ȼ���

		glActiveTexture(GL_TEXTURE0); // ��������Ԫ
		glBindTexture(GL_TEXTURE_2D, TexBufferA); // ������
		glActiveTexture(GL_TEXTURE3); // ��������Ԫ
		glBindTexture(GL_TEXTURE_2D, TexBufferB); // ������
		glBindVertexArray(VAO); // ��VAO
		// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // ��EBO

		viewMat = camera.GetViewMatrix(); // ��ȡ�۲����

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 modelMat2; // ģ�;���
			modelMat2 = glm::translate(modelMat2, cubePositions[i]); // λ��

			myShader->use(); // ʹ����ɫ������

			glUniform1i(glGetUniformLocation(myShader->id, "ourTexture"), 0); // �ֶ���������Ԫ
			glUniform1i(glGetUniformLocation(myShader->id, "ourFace"), 3); // �ֶ���������Ԫ
			// glUniformMatrix4fv(glGetUniformLocation(myShader->id, "transform"), 1, GL_FALSE, glm::value_ptr(trans)); // �ֶ���������Ԫ
			glUniformMatrix4fv(glGetUniformLocation(myShader->id, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2)); // �ֶ���������Ԫ
			glUniformMatrix4fv(glGetUniformLocation(myShader->id, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat)); // �ֶ���������Ԫ
			glUniformMatrix4fv(glGetUniformLocation(myShader->id, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat)); // �ֶ���������Ԫ

			// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // ����������, 6������, ��������, ƫ����
			glDrawArrays(GL_TRIANGLES, 0, 36); // ����������, 36������
		}

		// ������ɫ����
		glfwSwapBuffers(window);
		// �����û�д���ʲô�¼�������������롢����ƶ��ȣ���Ȼ����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
		glfwPollEvents();
		camera.UpdateCameraPosition();
	}

	// �ͷ�GLFW������ڴ�
	glfwTerminate();

	return 0;
}