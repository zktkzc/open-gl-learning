#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned> _indices, std::vector<Texture> _textures)
	: vertices(_vertices), indices(_indices), textures(_textures)
{
}

void Mesh::Draw(Shader* _shader)
{
}

void Mesh::SetupMesh()
{
}
