#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

// ������ɫ��
const char* vertexShaderSource =
"#version 330 core \n " // �汾��
"layout(location = 6) in vec3 aPos; \n " // λ�ñ���������λ��ֵΪ6
"layout(location = 7) in vec3 aColor; \n " // ��ɫ����������λ��ֵΪ7
"out vec4 vertexColor; \n " // �������
"void main(){ \n " // ������
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // gl_Position��һ��vec4������������������Ǳ����vec3��positionת��Ϊvec4
"	vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0); \n" // �������������Ϊ����ɫ
"}";

// Ƭ����ɫ��
const char* fragmentShaderSource =
"#version 330 core \n " // �汾��
"in vec4 vertexColor; \n " // �������
"uniform vec4 ourColor; \n" // uniform������������CPU�е�Ӧ�ó��������ݵ�GPU����ɫ�������У�ʹ��uniform֮ǰ������������
"out vec4 color; \n " // �������
"void main(){ \n " // ������
"	color = vertexColor;}"; // �������������Ϊ�����������ɫֵ

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

	// ����������ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // ����һ����ɫ������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // ����ɫ��Դ�븽�ӵ���ɫ��������
	glCompileShader(vertexShader); // ���붥����ɫ��

	// ����Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // ����һ����ɫ������
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // ����ɫ��Դ�븽�ӵ���ɫ��������
	glCompileShader(fragmentShader); // ����Ƭ����ɫ��

	// ����һ���������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// ���Ӷ�����ɫ����Ƭ����ɫ��
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// ���ӳ���
	glLinkProgram(shaderProgram);

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

		float timeValue = glfwGetTime(); // ��ȡ��ǰʱ��
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f; // ʹ��ɫֵ��0.0f��1.0f֮��
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); // ��ȡuniform������λ��ֵ

		glUseProgram(shaderProgram); // ʹ����ɫ������

		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); // ����uniform������ֵ

		//glDrawArrays(GL_TRIANGLES, 0, 6); // ����������
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