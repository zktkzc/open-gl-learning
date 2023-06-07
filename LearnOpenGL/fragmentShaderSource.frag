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

struct LightDirectional
{
	vec3 pos; // ��Դλ��
	vec3 color; // ��Դ��ɫ
	vec3 dirToLight; // ��Դ����
};

struct LightPoint
{
	vec3 pos; // ��Դλ��
	vec3 color; // ��Դ��ɫ
	vec3 dirToLight; // ��Դ����
	float constant; // ������
	float linear; // һ����
	float quadratic; // ������
};

struct LightSpot
{
	vec3 pos; // ��Դλ��
	vec3 color; // ��Դ��ɫ
	vec3 dirToLight; // ��Դ����
	float cosPhyInner;
	float cosPhyOuter;
};

uniform Material material; // �������

uniform LightDirectional lightD; // ƽ�й��Դ
uniform LightPoint lightP0; // ���Դ
uniform LightPoint lightP1; // ���Դ
uniform LightPoint lightP2; // ���Դ
uniform LightPoint lightP3; // ���Դ
uniform LightSpot lightS; // �۹�ƹ�Դ

uniform vec3 objColor; // ������ɫ
uniform vec3 ambientColor; // ��������
uniform vec3 cameraPos; // �����λ��

out vec4 FragColor; // �����ɫ����Ⱦ����

vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera)
{
	// diffuse
	float diffIntensity = max(dot(light.dirToLight, uNormal), 0.0f);
	vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	// specular
	vec3 R = normalize(reflect(-light.dirToLight, uNormal)); // �����������ӹ�Դ��������Ƭ��
	float specIntensity = pow(max(dot(R, dirToCamera), 0.0f), material.shininess);
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera)
{
	// attenuation ˥��
	float dist = length(light.pos - FragPos); // ��Դ��Ƭ�εľ���
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	// diffuse
	float diffIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0.0f) * attenuation;
	vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	// specular
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal)); // �����������ӹ�Դ��������Ƭ��
	float specIntensity = pow(max(dot(R, dirToCamera), 0.0f), material.shininess) * attenuation;
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
};

void main()
{
	vec3 finalResult = vec3(0, 0, 0);
	vec3 uNormal = normalize(Normal); // Ƭ�ε�λ������
	vec3 dirToCamera = normalize(cameraPos - FragPos); // Ƭ��ָ��������ķ�������

	finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);

	finalResult += CalcLightPoint(lightP0, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP1, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP2, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP3, uNormal, dirToCamera);

	FragColor = vec4(finalResult, 1.0f);
}