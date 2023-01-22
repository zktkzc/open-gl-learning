#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ��������
GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.8f,  0.8f, 0.0f
};

// ������ɫ��
const char* vertexShaderSource =
"#version 330 core \n "
"layout(location = 0) in vec3 position; \n "
"void main(){ \n "
"	gl_Position = vec4(position.x, position.y, position.z, 1.0);}";

// Ƭ����ɫ��
const char* fragmentShaderSource =
"#version 330 core \n "
"out vec4 color; \n "
"void main(){ \n "
"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);}";

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
	// ����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ����glfw����
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Create GLFW window failed!");
		glfwTerminate(); // ��ֹ
		return -1;
	}

	glfwMakeContextCurrent(window); // ���õ�ǰ������

	// ��ʼ��glew
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW failed!");
		glfwTerminate();
		return -1;
	}
	// ���ô��ڵ�ά��
	glViewport(0, 0, 800, 600);
	// �����޳�
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

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

	// ����������ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// ����Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// ����һ���������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// ���Ӷ�����ɫ����Ƭ����ɫ��
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// ���ӳ���
	glLinkProgram(shaderProgram);

	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) // ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
	{
		processInput(window);

		// �����ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// �����ɫ����
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// ������ɫ����
		glfwSwapBuffers(window);
		// �����û�д���ʲô�¼�������������롢����ƶ��ȣ���Ȼ����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
		glfwPollEvents();
	}

	// �ͷ�GLFW������ڴ�
	glfwTerminate();

	return 0;
}