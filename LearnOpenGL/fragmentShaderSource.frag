#version 330 core
in vec3 FragPos; // Ƭ������������ϵ�е�λ��
in vec3 Normal; // Ƭ�εķ���
in vec2 TexCoord; // Ƭ�ε���������

struct Material
{
	vec3 ambient; // ��������
	sampler2D diffuse; // ��������ͼ
	sampler2D specular; // ���淴��
	float shininess; // ���淴��ǿ��
};

struct LightPoint
{
	float constant; // ������
	float linear; // һ����
	float quadratic; // ������
};

uniform Material material; // �������
uniform LightPoint lightPoint; // ���Դ

// uniform sampler2D ourTexture;
// uniform sampler2D ourFace; 
uniform vec3 objColor; // ������ɫ
uniform vec3 ambientColor; // ��������
uniform vec3 lightPos; // ��Դλ��
uniform vec3 lightDirUniform; // ��Դ����
uniform vec3 lightColor; // ��Դ��ɫ
uniform vec3 cameraPos; // �����λ��

out vec4 FragColor; // �����ɫ����Ⱦ����

void main()
{
	float dist = length(lightPos - FragPos); // �����Դ��Ƭ��֮��ľ���
	float attenuation = 1.0 / (lightPoint.constant + lightPoint.linear * dist + lightPoint.quadratic * (dist * dist)); // ����˥��ϵ��
	vec3 lightDir = normalize(lightPos - FragPos); // ��Դ����, ������ָ���Դ
	vec3 reflectVec = reflect(-lightDir, Normal); // ���㷴������, ���ߴ�����ָ���Դ, ������ָ�������ⲿ, ����������Ҫȡ��
	vec3 cameraVec = normalize(cameraPos - FragPos); // ���������, ������ָ�������
	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess); // ���㾵�淴��ǿ��, ˥��ָ��Ϊ32��Խ��Խ����ԽСԽ��
	vec3 specular = texture(material.specular, TexCoord).rgb * specularAmount * lightColor; // ���淴����ɫ
	vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max(dot(lightDir, Normal), 0) * lightColor; // ��������ɫ
	// vec3 diffuse = texture(material.diffuse, TexCoord).rgb; // ��������ɫ
	vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientColor; // ����������ɫ
	FragColor = vec4((ambient + (diffuse + specular) * attenuation) * objColor, 1.0); // ������ɫ = �������� + ������ + ���淴��
}