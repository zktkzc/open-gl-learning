#include "Model.h"

Model::Model(std::string path)
{
	load_model(path);
}

void Model::load_model(std::string path)
{
	Assimp::Importer importer; // 创建导入器
	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
	); // 读取模型文件  三角化 | 翻转UV坐标 | 计算切线空间
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl; // 输出错误信息
		return;
	}
	directory = path.substr(0, path.find_last_of('\\')); // 获取模型所在目录
	// std::cout << "Success! Model::load_model: directory = " << directory << std::endl;

	process_node(scene->mRootNode, scene); // 处理根节点
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
	// std::cout << "节点名称：" << node->mName.data << std::endl;

	for (unsigned int i = 0; i < node->mChildren; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]]; // 处理网格
		// meshes.push_back();
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		process_node(node->mChildren[i], scene); // 递归处理子节点
	}
}
