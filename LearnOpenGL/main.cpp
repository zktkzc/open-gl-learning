#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

// ��������
GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0, 0, // ���½�
	 0.5f, -0.5f, 0.0f, 0, 1.0f, 0, // ���½�
	 0.0f,  0.5f, 0.0f, 0, 0, 1.0f, // ����
	 /*0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,*/
	 0.8f,  0.8f, 0.0f, 1.0f, 0, 1.0f // ���Ͻ�
};

// ��������
unsigned int indices[] = { // ��ʱ�����Ϊ����
	0, 1, 2,
	2, 1, 3
};

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // �������Esc��
	{
		// �趨WindowShouldClose����Ϊtrue�Ӷ��ر�GLFW
		glfwSetWindowShouldClose(window, true);
	}
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
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0); // ������������
	glEnableVertexAttribArray(6); // ���ö�������
	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float))); // ������ɫ����
	glEnableVertexAttribArray(7); // ���ö�������

	while (!glfwWindowShouldClose(window)) // ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
	{
		processInput(window);

		// �����ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// �����ɫ����
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO); // ��VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // ��EBO

		myShader->use(); // ʹ����ɫ������

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // ����������, 6������, ��������, ƫ����

		// ������ɫ����
		glfwSwapBuffers(window);
		// �����û�д���ʲô�¼�������������롢����ƶ��ȣ���Ȼ����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
		glfwPollEvents();
	}

	// �ͷ�GLFW������ڴ�
	glfwTerminate();

	return 0;
}