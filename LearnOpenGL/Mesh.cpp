#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures)
{
	this->vertices = _vertices;
	this->indices = _indices;
	this->textures = _textures;
}

// 绘制贴图
void Mesh::Draw(Shader* _shader)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].type == "texture_diffuse")
		{
			glActiveTexture(GL_TEXTURE0); // 激活纹理单元0
			glBindTexture(GL_TEXTURE_2D, textures[i].id); // 绑定纹理
			_shader->SetUniform1i("material.diffuse", 0); // 设置uniform变量
		}
		else if (textures[i].type == "texture_specular")
		{
			glActiveTexture(GL_TEXTURE1); // 激活纹理单元1
			glBindTexture(GL_TEXTURE_2D, textures[i].id); // 绑定纹理
			_shader->SetUniform1i("material.specular", 1); // 设置uniform变量
		}

		glBindVertexArray(VAO); // 绑定顶点数组对象
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // 绘制网格
		glBindVertexArray(0); // 解绑顶点数组对象
		glActiveTexture(GL_TEXTURE0); // 激活纹理单元0
	}
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
