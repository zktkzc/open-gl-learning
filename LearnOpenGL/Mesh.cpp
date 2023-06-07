#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures)
{
	this->vertices = _vertices;
	this->indices = _indices;
	this->textures = _textures;
}

void Mesh::Draw(Shader* _shader)
{
}

// 初始化网格
void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO); // 生成顶点数组对象
	glBindVertexArray(VAO); // 绑定顶点数组对象

	glGenBuffers(1, &VBO); // 生成顶点缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定顶点缓冲对象
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vertex),
		&vertices[0],
		GL_STATIC_DRAW
	); // 将顶点数据复制到顶点缓冲对象中

	glGenBuffers(1, &EBO); // 生成索引缓冲对象
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // 绑定索引缓冲对象
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(unsigned int),
		&indices[0],
		GL_STATIC_DRAW
	); // 将索引数据复制到索引缓冲对象中

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)0
	); // 设置顶点属性指针
	glEnableVertexAttribArray(0); // 启用顶点属性
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)3
	); // 设置顶点属性指针
	glEnableVertexAttribArray(1); // 启用顶点属性
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)6
	); // 设置顶点属性指针
	glEnableVertexAttribArray(2); // 启用顶点属性
}
