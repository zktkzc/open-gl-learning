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
		//meshes.push_back();
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		process_node(node->mChildren[i], scene); // �ݹ鴦���ӽڵ�
	}
}

// �������񣬽�aiMeshת��Ϊ�����Լ������Mesh
Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tmpVertices; // ��������
	std::vector<unsigned int> tmpIndices; // ��������
	std::vector<Texture> tmpTextures; // ��ͼ����

	glm::vec3 tmpVec;
	// ������
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex tmpVertex;

		tmpVertex.Position.x = mesh->mVertices[i].x;
		tmpVertex.Position.y = mesh->mVertices[i].y;
		tmpVertex.Position.z = mesh->mVertices[i].z;

		tmpVertex.Normal.x = mesh->mNormals[i].x;
		tmpVertex.Normal.y = mesh->mNormals[i].y;
		tmpVertex.Normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			// һ����������ж���������꣬����ֻȡ��һ��
			tmpVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tmpVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			// ���û���������꣬�ͽ�������������Ϊ0
			tmpVertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		tmpVertices.push_back(tmpVertex);
	}

	// ��������
	for (unsigned int i = 0; i < mesh->mFaces->mNumIndices; i++)
	{
		tmpIndices.push_back(mesh->mFaces->mIndices[i]);
	}

	return Mesh(tmpVertices, tmpIndices, {});
}
