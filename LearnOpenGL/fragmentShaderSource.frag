#version 330 core
in vec3 FragPos;
in vec3 Normal;

// uniform sampler2D ourTexture;
// uniform sampler2D ourFace; 
uniform vec3 objColor; // 物体颜色
uniform vec3 ambientColor; // 环境光照
uniform vec3 lightPos; // 光源位置
uniform vec3 lightColor; // 光源颜色

out vec4 FragColor;

void main()
{
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 diffuse = dot(lightDir, Normal) * lightColor;
	FragColor = vec4((ambientColor + diffuse) * objColor, 1.0);
}