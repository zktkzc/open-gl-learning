#version 330 core
in vec3 FragPos;
in vec3 Normal;

// uniform sampler2D ourTexture;
// uniform sampler2D ourFace; 
uniform vec3 objColor; // ������ɫ
uniform vec3 ambientColor; // ��������
uniform vec3 lightPos; // ��Դλ��
uniform vec3 lightColor; // ��Դ��ɫ

out vec4 FragColor;

void main()
{
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 diffuse = dot(lightDir, Normal) * lightColor;
	FragColor = vec4((ambientColor + diffuse) * objColor, 1.0);
}