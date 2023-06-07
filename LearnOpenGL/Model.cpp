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
		//meshes.push_back();
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		process_node(node->mChildren[i], scene); // 递归处理子节点
	}
}

// 处理网格，将aiMesh转换为我们自己定义的Mesh
Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tmpVertices; // 顶点数组
	std::vector<unsigned int> tmpIndices; // 索引数组
	std::vector<Texture> tmpTextures; // 贴图数组

	glm::vec3 tmpVec;
	// 处理顶点
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
			// 一个顶点可能有多个纹理坐标，我们只取第一个
			tmpVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tmpVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			// 如果没有纹理坐标，就将纹理坐标设置为0
			tmpVertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		tmpVertices.push_back(tmpVertex);
	}

	// 处理索引
	for (unsigned int i = 0; i < mesh->mFaces->mNumIndices; i++)
	{
		tmpIndices.push_back(mesh->mFaces->mIndices[i]);
	}

	return Mesh(tmpVertices, tmpIndices, {});
}
