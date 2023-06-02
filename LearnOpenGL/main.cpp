#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// 顶点数组
GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 /*0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,*/
	 0.8f,  0.8f, 0.0f
};

// 索引数组
unsigned int indices[] = { // 逆时针绘制为正面
	0, 1, 2,
	2, 1, 3
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

	// 背面剔除
	// glEnable(GL_CULL_FACE); // 启用面剔除
	// glCullFace(GL_BACK); // 剔除背面

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 设置绘制模式为线框模式

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

	unsigned int EBO; // 索引缓冲对象(Element Buffer Object, EBO)
	glGenBuffers(1, &EBO); // 生成一个索引缓冲对象
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // 把新创建的缓冲绑定到GL_ELEMENT_ARRAY_BUFFER目标上
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // 把用户定义的数据复制到当前绑定缓冲的函数

	// 创建顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // 创建一个着色器对象
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // 把着色器源码附加到着色器对象上
	glCompileShader(vertexShader); // 编译顶点着色器

	// 创建片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // 创建一个着色器对象
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // 把着色器源码附加到着色器对象上
	glCompileShader(fragmentShader); // 编译片段着色器

	// 创建一个程序对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// 附加顶点着色器和片段着色器
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// 链接程序
	glLinkProgram(shaderProgram);

	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0); // 解析顶点数据
	glEnableVertexAttribArray(0); // 启用顶点属性

	while (!glfwWindowShouldClose(window)) // 每次循环的开始前检查一次GLFW是否被要求退出
	{
		processInput(window);

		// 清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// 清除颜色缓冲
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO); // 绑定VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // 绑定EBO
		glUseProgram(shaderProgram); // 使用着色器程序
		//glDrawArrays(GL_TRIANGLES, 0, 6); // 绘制三角形
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 绘制三角形, 6个顶点, 索引类型, 偏移量

		// 交换颜色缓冲
		glfwSwapBuffers(window);
		// 检查有没有触发什么事件（比如键盘输入、鼠标移动等），然后调用对应的回调函数（可以通过回调方法手动设置）
		glfwPollEvents();
	}

	// 释放GLFW分配的内存
	glfwTerminate();

	return 0;
}