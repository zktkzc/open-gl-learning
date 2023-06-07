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

struct LightPoint
{
	float constant; // 常数项
	float linear; // 一次项
	float quadratic; // 二次项
};

uniform Material material; // 物体材质
uniform LightPoint lightPoint; // 点光源

// uniform sampler2D ourTexture;
// uniform sampler2D ourFace; 
uniform vec3 objColor; // 物体颜色
uniform vec3 ambientColor; // 环境光照
uniform vec3 lightPos; // 光源位置
uniform vec3 lightDirUniform; // 光源方向
uniform vec3 lightColor; // 光源颜色
uniform vec3 cameraPos; // 摄像机位置

out vec4 FragColor; // 输出颜色到渲染缓冲

void main()
{
	float dist = length(lightPos - FragPos); // 计算光源和片段之间的距离
	float attenuation = 1.0 / (lightPoint.constant + lightPoint.linear * dist + lightPoint.quadratic * (dist * dist)); // 计算衰减系数
	vec3 lightDir = normalize(lightPos - FragPos); // 光源方向, 从物体指向光源
	vec3 reflectVec = reflect(-lightDir, Normal); // 计算反射向量, 光线从物体指向光源, 法向量指向物体外部, 所以这里需要取反
	vec3 cameraVec = normalize(cameraPos - FragPos); // 摄像机方向, 从物体指向摄像机
	float specularAmount = pow(max(dot(reflectVec, cameraVec), 0), material.shininess); // 计算镜面反射强度, 衰减指数为32，越大越亮，越小越暗
	vec3 specular = texture(material.specular, TexCoord).rgb * specularAmount * lightColor; // 镜面反射颜色
	vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max(dot(lightDir, Normal), 0) * lightColor; // 漫反射颜色
	// vec3 diffuse = texture(material.diffuse, TexCoord).rgb; // 漫反射颜色
	vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientColor; // 环境光照颜色
	FragColor = vec4((ambient + (diffuse + specular) * attenuation) * objColor, 1.0); // 物体颜色 = 环境光照 + 漫反射 + 镜面反射
}