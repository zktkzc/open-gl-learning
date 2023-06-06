#version 330 core
in vec3 FragPos; // Ƭ������������ϵ�е�λ��
in vec3 Normal; // Ƭ�εķ���

// uniform sampler2D ourTexture;
// uniform sampler2D ourFace; 
uniform vec3 objColor; // ������ɫ
uniform vec3 ambientColor; // ��������
uniform vec3 lightPos; // ��Դλ��
uniform vec3 lightColor; // ��Դ��ɫ
uniform vec3 cameraPos; // �����λ��

out vec4 FragColor; // �����ɫ����Ⱦ����

void main()
{
	vec3 lightDir = normalize(lightPos - FragPos); // ��Դ����, ������ָ���Դ
	vec3 reflectVec = reflect(-lightDir, Normal); // ���㷴������, ���ߴ�����ָ���Դ, ������ָ�������ⲿ, ����������Ҫȡ��
	vec3 cameraVec = normalize(cameraPos - FragPos); // ���������, ������ָ�������
	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), 32); // ���㾵�淴��ǿ��, ˥��ָ��Ϊ32��Խ��Խ����ԽСԽ��
	vec3 specular = specularAmount * lightColor; // ���淴����ɫ
	vec3 diffuse = max(dot(lightDir, Normal), 0) * lightColor; // ��������ɫ
	FragColor = vec4((ambientColor + diffuse + specular) * objColor, 1.0); // ������ɫ = �������� + ������ + ���淴��
}