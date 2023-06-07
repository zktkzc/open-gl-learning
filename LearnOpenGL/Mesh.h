#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "Shader.h"

// ����ṹ��
struct Vertex
{
	glm::vec3 Position; // λ��
	glm::vec3 Normal; // ������
	glm::vec2 TexCoords; // ��������
};

// ��ͼ�ṹ��
struct Texture
{
	unsigned int id; // ��ͼid
	std::string type; // ��ͼ����
	std::string path; // ��ͼ·��
};

class Mesh
{
public:
	Mesh(float vertices[]);
	Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures);
	~Mesh() = default;
	void Draw(Shader* _shader);

private:
	void SetupMesh();

public:
	std::vector<Vertex> vertices; // ��������
	std::vector<unsigned int> indices; // ��������
	std::vector<Texture> textures; // ��ͼ����

private:
	unsigned int VAO, VBO, EBO;
};
