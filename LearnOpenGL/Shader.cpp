#include "Shader.h"

Shader::Shader(const char* veretexPath, const char* fragmentPath)
{
	std::ifstream vertexFile; // 文件流
	std::ifstream fragmentFile;

	std::stringstream vertexSStream; // 字符串流
	std::stringstream fragmentSStream;

	vertexFile.open(veretexPath); // 打开文件
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit); // 设置异常标志位
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
			throw std::exception("Vertex file or fragment file open failed!"); // 抛出异常
		vertexSStream << vertexFile.rdbuf(); // 读取文件到字符串流
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str(); // 字符串流转换为字符串
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str(); // 字符串转换为const char*
		fragmentSource = fragmentString.c_str();

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // 创建着色器对象
		glShaderSource(vertexShader, 1, &vertexSource, NULL); // 把着色器源码附加到着色器对象上
		glCompileShader(vertexShader); // 编译顶点着色器

		int success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // 获取编译状态
		if (!success) // 编译失败
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // 获取错误信息
			throw std::exception(infoLog); // 抛出异常
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // 创建着色器对象
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // 把着色器源码附加到着色器对象上
		glCompileShader(fragmentShader); // 编译片段着色器

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // 获取编译状态
		if (!success) // 编译失败
		{
			char infoLog[512];
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); // 获取错误信息
			throw std::exception(infoLog); // 抛出异常
		}

		id = glCreateProgram(); // 创建着色器程序对象
		glAttachShader(id, vertexShader); // 把着色器附加到着色器程序上
		glAttachShader(id, fragmentShader);
		glLinkProgram(id); // 链接着色器程序

		glGetProgramiv(id, GL_LINK_STATUS, &success); // 获取链接状态
		if (!success) // 链接失败
		{
			char infoLog[512];
			glGetProgramInfoLog(id, 512, NULL, infoLog); // 获取错误信息
			throw std::exception(infoLog); // 抛出异常
		}

		glDeleteShader(vertexShader); // 删除着色器
		glDeleteShader(fragmentShader);
	}
	catch (const std::exception& e)
	{
		printf(e.what()); // 输出错误信息
	}
}

/// <summary>
/// 使用着色器程序
/// </summary>
void Shader::use()
{
	glUseProgram(id); // 使用着色器程序
}
