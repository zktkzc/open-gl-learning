#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures)
{
	this->vertices = _vertices;
	this->indices = _indices;
	this->textures = _textures;
}

// ������ͼ
void Mesh::Draw(Shader* _shader)
{
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i].type == "texture_diffuse")
		{
			glActiveTexture(GL_TEXTURE0); // ��������Ԫ0
			glBindTexture(GL_TEXTURE_2D, textures[i].id); // ������
			_shader->SetUniform1i("material.diffuse", 0); // ����uniform����
		}
		else if (textures[i].type == "texture_specular")
		{
			glActiveTexture(GL_TEXTURE1); // ��������Ԫ1
			glBindTexture(GL_TEXTURE_2D, textures[i].id); // ������
			_shader->SetUniform1i("material.specular", 1); // ����uniform����
		}

		glBindVertexArray(VAO); // �󶨶����������
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); // ��������
		glBindVertexArray(0); // ��󶥵��������
		glActiveTexture(GL_TEXTURE0); // ��������Ԫ0
	}
}

// ��ʼ������
void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO); // ���ɶ����������
	glBindVertexArray(VAO); // �󶨶����������

	glGenBuffers(1, &VBO); // ���ɶ��㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // �󶨶��㻺�����
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vertex),
		&vertices[0],
		GL_STATIC_DRAW
	); // ���������ݸ��Ƶ����㻺�������

	glGenBuffers(1, &EBO); // ���������������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // �������������
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(unsigned int),
		&indices[0],
		GL_STATIC_DRAW
	); // ���������ݸ��Ƶ��������������

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)0
	); // ���ö�������ָ��
	glEnableVertexAttribArray(0); // ���ö�������
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)3
	); // ���ö�������ָ��
	glEnableVertexAttribArray(1); // ���ö�������
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)6
	); // ���ö�������ָ��
	glEnableVertexAttribArray(2); // ���ö�������
}
