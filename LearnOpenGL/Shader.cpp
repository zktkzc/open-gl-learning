#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vertexFile; // �ļ���
	std::ifstream fragmentFile;

	std::stringstream vertexSStream; // �ַ�����
	std::stringstream fragmentSStream;

	vertexFile.open(vertexPath); // ���ļ�
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit); // �����쳣��־λ
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
			throw std::exception("Vertex file or fragment file open failed!"); // �׳��쳣
		vertexSStream << vertexFile.rdbuf(); // ��ȡ�ļ����ַ�����
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str(); // �ַ�����ת��Ϊ�ַ���
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str(); // �ַ���ת��Ϊconst char*
		fragmentSource = fragmentString.c_str();

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // ������ɫ������
		glShaderSource(vertexShader, 1, &vertexSource, NULL); // ����ɫ��Դ�븽�ӵ���ɫ��������
		glCompileShader(vertexShader); // ���붥����ɫ��

		int success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // ��ȡ����״̬
		if (!success) // ����ʧ��
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // ��ȡ������Ϣ
			throw std::exception(infoLog); // �׳��쳣
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // ������ɫ������
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // ����ɫ��Դ�븽�ӵ���ɫ��������
		glCompileShader(fragmentShader); // ����Ƭ����ɫ��

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // ��ȡ����״̬
		if (!success) // ����ʧ��
		{
			char infoLog[512];
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog); // ��ȡ������Ϣ
			throw std::exception(infoLog); // �׳��쳣
		}

		id = glCreateProgram(); // ������ɫ���������
		glAttachShader(id, vertexShader); // ����ɫ�����ӵ���ɫ��������
		glAttachShader(id, fragmentShader);
		glLinkProgram(id); // ������ɫ������

		glGetProgramiv(id, GL_LINK_STATUS, &success); // ��ȡ����״̬
		if (!success) // ����ʧ��
		{
			char infoLog[512];
			glGetProgramInfoLog(id, 512, NULL, infoLog); // ��ȡ������Ϣ
			throw std::exception(infoLog); // �׳��쳣
		}

		glDeleteShader(vertexShader); // ɾ����ɫ��
		glDeleteShader(fragmentShader);
	}
	catch (const std::exception& e)
	{
		printf(e.what()); // ���������Ϣ
	}
}

/// <summary>
/// ʹ����ɫ������
/// </summary>
void Shader::use()
{
	glUseProgram(id); // ʹ����ɫ������
}

void Shader::SetUniform3f(const char* paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(this->id, paramNameString), param.x, param.y, param.z);
}

void Shader::SetUniform1f(const char* paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(this->id, paramNameString), param);
}

void Shader::SetUniform1i(const char* paramNameString, int slot)
{
	glUniform1i(glGetUniformLocation(this->id, paramNameString), slot);
}
