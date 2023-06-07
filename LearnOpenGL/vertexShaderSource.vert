#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 modelMat; // ģ�;���
uniform mat4 viewMat; // ��ͼ����
uniform mat4 projectionMat; // ͶӰ����

out vec3 FragPos; // Ƭ�ε���������
out vec3 Normal; // Ƭ�εķ���
out vec2 TexCoord; // Ƭ�ε���������

void main()
{
	gl_Position = projectionMat * viewMat * modelMat * vec4(aPos.xyz, 1.0); // �����������ģ�;�����ͼ����ͶӰ���󣬵õ��ü��ռ�����
	FragPos = (modelMat * vec4(aPos.xyz, 1.0)).xyz; // �����������ģ�;��󣬵õ���������
	Normal = mat3(transpose(inverse(modelMat))) * aNormal; // ���߳���ģ�;������ת�þ�����Ϊģ�;�����������ţ�������Ҫ��ת�þ���
	TexCoord = aTexCoord; // ��������
};