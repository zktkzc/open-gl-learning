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
	std::cout << "Success! Model::load_model: directory = " << directory << std::endl;
}
