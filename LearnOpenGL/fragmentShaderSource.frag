#version 330 core
in vec3 FragPos; // 片段在世界坐标系中的位置
in vec3 Normal; // 片段的法线
in vec2 TexCoord; // 片段的纹理坐标

struct Material
{
	vec3 ambient; // 环境光照
	sampler2D diffuse; // 漫反射贴图
	sampler2D specular; // 镜面反射
	float shininess; // 镜面反射强度
};

struct LightDirectional
{
	vec3 pos; // 光源位置
	vec3 color; // 光源颜色
	vec3 dirToLight; // 光源方向
};

struct LightPoint
{
	vec3 pos; // 光源位置
	vec3 color; // 光源颜色
	vec3 dirToLight; // 光源方向
	float constant; // 常数项
	float linear; // 一次项
	float quadratic; // 二次项
};

struct LightSpot
{
	vec3 pos; // 光源位置
	vec3 color; // 光源颜色
	vec3 dirToLight; // 光源方向
	float cosPhyInner;
	float cosPhyOuter;
};

uniform Material material; // 物体材质

uniform LightDirectional lightD; // 平行光光源
uniform LightPoint lightP0; // 点光源
uniform LightPoint lightP1; // 点光源
uniform LightPoint lightP2; // 点光源
uniform LightPoint lightP3; // 点光源
uniform LightSpot lightS; // 聚光灯光源

uniform vec3 objColor; // 物体颜色
uniform vec3 ambientColor; // 环境光照
uniform vec3 cameraPos; // 摄像机位置

out vec4 FragColor; // 输出颜色到渲染缓冲

vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera)
{
	// diffuse
	float diffIntensity = max(dot(light.dirToLight, uNormal), 0.0f);
	vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	// specular
	vec3 R = normalize(reflect(-light.dirToLight, uNormal)); // 反射向量，从光源出发照向片段
	float specIntensity = pow(max(dot(R, dirToCamera), 0.0f), material.shininess);
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

vec3 CalcLightPoint(LightPoint light, vec3 uNormal, vec3 dirToCamera)
{
	// attenuation 衰减
	float dist = length(light.pos - FragPos); // 光源到片段的距离
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	// diffuse
	float diffIntensity = max(dot(normalize(light.pos - FragPos), uNormal), 0.0f) * attenuation;
	vec3 diffColor = diffIntensity * light.color * texture(material.diffuse, TexCoord).rgb;

	// specular
	vec3 R = normalize(reflect(-normalize(light.pos - FragPos), uNormal)); // 反射向量，从光源出发照向片段
	float specIntensity = pow(max(dot(R, dirToCamera), 0.0f), material.shininess) * attenuation;
	vec3 specColor = specIntensity * light.color * texture(material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
};

void main()
{
	vec3 finalResult = vec3(0, 0, 0);
	vec3 uNormal = normalize(Normal); // 片段单位法向量
	vec3 dirToCamera = normalize(cameraPos - FragPos); // 片段指向摄像机的方向向量

	finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);

	finalResult += CalcLightPoint(lightP0, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP1, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP2, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP3, uNormal, dirToCamera);

	FragColor = vec4(finalResult, 1.0f);
}