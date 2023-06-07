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
	void process_node(aiNode* node, const aiScene* scene);

public:
	std::vector<Mesh> meshes; // 网格数组
	std::string directory; // 模型所在目录
};

