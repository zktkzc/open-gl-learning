#version 330 core
layout(location = 6) in vec3 aPos;
layout(location = 9) in vec3 aNormal;

uniform mat4 modelMat; // 模型矩阵
uniform mat4 viewMat; // 视图矩阵
uniform mat4 projectionMat; // 投影矩阵

out vec3 FragPos; // 片段的世界坐标
out vec3 Normal; // 片段的法线

void main()
{
	gl_Position = projectionMat * viewMat * modelMat * vec4(aPos.xyz, 1.0); // 顶点坐标乘以模型矩阵，视图矩阵，投影矩阵，得到裁剪空间坐标
	FragPos = (modelMat * vec4(aPos.xyz, 1.0)).xyz; // 顶点坐标乘以模型矩阵，得到世界坐标
	Normal = mat3(transpose(inverse(modelMat))) * aNormal; // 法线乘以模型矩阵的逆转置矩阵，因为模型矩阵包含了缩放，所以需要逆转置矩阵
};