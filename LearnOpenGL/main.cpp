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
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"

#pragma region ģ������
// ��������
GLfloat vertices[] = {
	// Positions          // Normals           // Texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
#pragma endregion

#pragma region ���������
Camera camera(glm::vec3(0, 0, 3.0f), 15.0f, 180.0f, glm::vec3(0, 1.0f, 0)); // ����һ�������
#pragma endregion

#pragma region ������Դ
LightDirectional lightD = LightDirectional(
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(glm::radians(90.0f), 0, 0),
	glm::vec3(1.0f, 1.0f, 1.0f)
); // ����һ��ƽ�й�

LightPoint lightP0 = LightPoint(
	glm::vec3(1.0f, 0, 0),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 0.0f, 0.0f)
); // ����һ�����Դ
LightPoint lightP1 = LightPoint(
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0.0f, 1.0f, 0.0f)
);
LightPoint lightP2 = LightPoint(
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0.0f, 0.0f, 1.0f)
);
LightPoint lightP3 = LightPoint(
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 1.0f, 1.0f)
);
#pragma endregion

#pragma region ������̺��������
float lastX; // �����һ֡Xλ��
float lastY; // �����һ֡Yλ��
bool firstMouse = false; // �Ƿ��ǵ�һ�������봰��


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
#pragma endregion

unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot)
{
	unsigned int TexBuffer; // ������������
	glGenTextures(1, &TexBuffer); // ��������
	glActiveTexture(GL_TEXTURE0 + textureSlot); // ��������Ԫ
	glBindTexture(GL_TEXTURE_2D, TexBuffer); // ������
	// ���������Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // ����S�ỷ�Ʒ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // ����T�ỷ�Ʒ�ʽ
	// ����������˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // ������С���˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // ���÷Ŵ���˷�ʽ


	// ���ز���������
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // ��תͼƬ
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0); // ����ͼƬ
	if (data)
	{
		// ��������
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data); // ��������
		glGenerateMipmap(GL_TEXTURE_2D); // Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
	}
	else
	{
		printf("Failed to load texture!");
	}
	stbi_image_free(data); // �ͷ�ͼ����ڴ�
	return TexBuffer;
}

int main()
{
#pragma region ��ʼ��GLFW������GLFW����������
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

	glEnable(GL_DEPTH_TEST); // ������Ȳ���
#pragma endregion

#pragma region ������ɫ������
	Shader* myShader = new Shader("vertexShaderSource.vert", "fragmentShaderSource.frag");
#pragma endregion

#pragma region ��������
	Material* myMaterial = new Material(
		myShader,
		LoadImageToGPU("container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
		LoadImageToGPU("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
		glm::vec3(1.0f, 1.0f, 1.0f),
		64.0f
	);
#pragma endregion

#pragma region ��ʼ���������ݣ���VAO��VBO
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

	// ���ö�������ָ��
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0); // ������������
	glEnableVertexAttribArray(6); // ���ö�������
	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float))); // ��������������
	glEnableVertexAttribArray(7); // ���ö�������
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float))); // ��������������
	glEnableVertexAttribArray(8); // ���ö�������
#pragma endregion

#pragma region ��������
	// ����
	//unsigned int TexBufferA = LoadImageToGPU("container.jpg", GL_RGB, GL_RGB, 0);
	//unsigned int TexBufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 3);
#pragma endregion

#pragma region ׼��ģ�;��󣬹۲����ͶӰ����
	glm::mat4 modelMat; // ģ�;���
	glm::mat4 viewMat; // �۲����
	glm::mat4 projectionMat; // ͶӰ����
	projectionMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // ͸��ͶӰ
#pragma endregion

#pragma region ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) // ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
	{
		processInput(window); // ��������

		// �����ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearColor(0, 0, 0, 1.0f);
		// �����ɫ����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ͬʱ�����Ȼ���

		viewMat = camera.GetViewMatrix(); // ��ȡ�۲����

		for (int i = 0; i < 10; i++)
		{
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]); // λ��

			myShader->use(); // ʹ����ɫ������

			glActiveTexture(GL_TEXTURE0); // ��������Ԫ
			glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse); // ������
			glActiveTexture(GL_TEXTURE0 + Shader::SPECULAR); // ��������Ԫ
			glBindTexture(GL_TEXTURE_2D, myMaterial->specular); // ������

			// glUniform1i(glGetUniformLocation(myShader->id, "ourTexture"), 0); // �ֶ���������Ԫ
			// glUniform1i(glGetUniformLocation(myShader->id, "ourFace"), 3); // �ֶ���������Ԫ
			glUniformMatrix4fv(
				glGetUniformLocation(myShader->id, "modelMat"),
				1,
				GL_FALSE,
				glm::value_ptr(modelMat)
			); // �ֶ���������Ԫ
			glUniformMatrix4fv(
				glGetUniformLocation(myShader->id, "viewMat"),
				1,
				GL_FALSE,
				glm::value_ptr(viewMat)
			); // �ֶ���������Ԫ
			glUniformMatrix4fv(
				glGetUniformLocation(myShader->id, "projectionMat"),
				1,
				GL_FALSE,
				glm::value_ptr(projectionMat)
			); // �ֶ���������Ԫ
			glUniform3f(glGetUniformLocation(myShader->id, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader->id, "ambientColor"), 0.3f, 0.3f, 0.3f);

#pragma region LightDirectional
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightD.pos"),
				lightD.position.x,
				lightD.position.y,
				lightD.position.z
			); // �ֶ���������Ԫ
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightD.color"),
				lightD.color.x,
				lightD.color.y,
				lightD.color.z
			); // �ֶ���������Ԫ
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightD.dirToLight"),
				lightD.direction.x,
				lightD.direction.y,
				lightD.direction.z
			); // �ֶ���������Ԫ
#pragma endregion

#pragma region LightPoint
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP0.pos"),
				lightP0.position.x,
				lightP0.position.y,
				lightP0.position.z
			); // �ֶ���������Ԫ
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP0.color"),
				lightP0.color.x,
				lightP0.color.y,
				lightP0.color.z
			); // �ֶ���������Ԫ
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP0.dirToLight"),
				lightP0.direction.x,
				lightP0.direction.y,
				lightP0.direction.z
			);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP0.constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP0.linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP0.quadratic"), lightP0.quadratic);

			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP1.pos"),
				lightP1.position.x,
				lightP1.position.y,
				lightP1.position.z
			); // �ֶ���������Ԫ
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP1.color"),
				lightP1.color.x,
				lightP1.color.y,
				lightP1.color.z
			); // �ֶ���������Ԫ
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP1.dirToLight"),
				lightP1.direction.x,
				lightP1.direction.y,
				lightP1.direction.z
			);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP1.constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP1.linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP1.quadratic"), lightP1.quadratic);

			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP2.pos"),
				lightP2.position.x,
				lightP2.position.y,
				lightP2.position.z
			); // �ֶ���������Ԫ
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP2.color"),
				lightP2.color.x,
				lightP2.color.y,
				lightP2.color.z
			); // �ֶ���������Ԫ
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP2.dirToLight"),
				lightP2.direction.x,
				lightP2.direction.y,
				lightP2.direction.z
			);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP2.constant"), lightP2.constant);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP2.linear"), lightP2.linear);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP2.quadratic"), lightP2.quadratic);

			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP3.pos"),
				lightP3.position.x,
				lightP3.position.y,
				lightP3.position.z
			); // �ֶ���������Ԫ
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP3.color"),
				lightP3.color.x,
				lightP3.color.y,
				lightP3.color.z
			); // �ֶ���������Ԫ
			glUniform3f(
				glGetUniformLocation(myShader->id, "lightP3.dirToLight"),
				lightP3.direction.x,
				lightP3.direction.y,
				lightP3.direction.z
			);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP3.constant"), lightP3.constant);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP3.linear"), lightP3.linear);
			glUniform1f(glGetUniformLocation(myShader->id, "lightP3.quadratic"), lightP3.quadratic);
#pragma endregion

#pragma region LightSpot
			// glUniform1f(glGetUniformLocation(myShader->id, "lightSpot.cosPhyInner"), light.cosPhyInner);
			// glUniform1f(glGetUniformLocation(myShader->id, "lightSpot.cosPhyOuter"), light.cosPhyOuter);
#pragma endregion

			glUniform3f(
				glGetUniformLocation(myShader->id, "cameraPos"),
				camera.Position.x,
				camera.Position.y,
				camera.Position.z
			); // �ֶ���������Ԫ

			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			//myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			//myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
			myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);

			glBindVertexArray(VAO); // ��VAO

			glDrawArrays(GL_TRIANGLES, 0, 36); // ����������, 36������
		}

		// ������ɫ����
		glfwSwapBuffers(window);
		// �����û�д���ʲô�¼�������������롢����ƶ��ȣ���Ȼ����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
		glfwPollEvents();
		camera.UpdateCameraPosition(); // ���������λ��
	}
#pragma endregion

	// �ͷ�GLFW������ڴ�
	glfwTerminate();

	return 0;
}