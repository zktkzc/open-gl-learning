#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "Shader.h"

// 顶点结构体
struct Vertex
{
	glm::vec3 Position; // 位置
	glm::vec3 Normal; // 法向量
	glm::vec2 TexCoords; // 纹理坐标
};

// 贴图结构体
struct Texture
{
	unsigned int id; // 贴图id
	std::string type; // 贴图类型
	std::string path; // 贴图路径
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
	std::vector<Vertex> vertices; // 顶点数组
	std::vector<unsigned int> indices; // 索引数组
	std::vector<Texture> textures; // 贴图数组

private:
	unsigned int VAO, VBO, EBO;
};
