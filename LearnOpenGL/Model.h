#pragma once
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>

#include "Mesh.h"

class Model
{
public:
	Model(std::string path);
	~Model() = default;

private:
	void load_model(std::string path);

public:
	std::vector<Mesh> meshes; // ��������
	std::string directory; // ģ������Ŀ¼
};

