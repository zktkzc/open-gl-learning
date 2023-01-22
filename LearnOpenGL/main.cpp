#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// 顶点数组
GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.8f,  0.8f, 0.0f
};

// 顶点着色器
const char* vertexShaderSource =
"#version 330 core \n "
"layout(location = 0) in vec3 position; \n "
"void main(){ \n "
"	gl_Position = vec4(position.x, position.y, position.z, 1.0);}";

// 片段着色器
const char* fragmentShaderSource =
"#version 330 core \n "
"out vec4 color; \n "
"void main(){ \n "
"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);}";

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // 如果按下Esc键
	{
		// 设定WindowShouldClose属性为true从而关闭GLFW
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	// 初始化GLFW
	glfwInit();
	// 配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建glfw窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
	if (window == NULL)
	{
		printf("Create GLFW window failed!");
		glfwTerminate(); // 终止
		return -1;
	}

	glfwMakeContextCurrent(window); // 设置当前上下文

	// 初始化glew
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW failed!");
		glfwTerminate();
		return -1;
	}
	// 设置窗口的维度
	glViewport(0, 0, 800, 600);
	// 背面剔除
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

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

	// 创建顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 创建片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 创建一个程序对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// 附加顶点着色器和片段着色器
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// 链接程序
	glLinkProgram(shaderProgram);

	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) // 每次循环的开始前检查一次GLFW是否被要求退出
	{
		processInput(window);

		// 清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// 清除颜色缓冲
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// 交换颜色缓冲
		glfwSwapBuffers(window);
		// 检查有没有触发什么事件（比如键盘输入、鼠标移动等），然后调用对应的回调函数（可以通过回调方法手动设置）
		glfwPollEvents();
	}

	// 释放GLFW分配的内存
	glfwTerminate();

	return 0;
}