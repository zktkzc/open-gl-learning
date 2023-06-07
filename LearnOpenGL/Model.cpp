#include "Model.h"

Model::Model(std::string path)
{
	load_model(path);
}

void Model::load_model(std::string path)
{
	Assimp::Importer importer; // ����������
	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
	); // ��ȡģ���ļ�  ���ǻ� | ��תUV���� | �������߿ռ�
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl; // ���������Ϣ
		return;
	}
	directory = path.substr(0, path.find_last_of('\\')); // ��ȡģ������Ŀ¼
	// std::cout << "Success! Model::load_model: directory = " << directory << std::endl;

	process_node(scene->mRootNode, scene); // ������ڵ�
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
	// std::cout << "�ڵ����ƣ�" << node->mName.data << std::endl;

	for (unsigned int i = 0; i < node->mChildren; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]]; // ��������
		// meshes.push_back();
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		process_node(node->mChildren[i], scene); // �ݹ鴦���ӽڵ�
	}
}
