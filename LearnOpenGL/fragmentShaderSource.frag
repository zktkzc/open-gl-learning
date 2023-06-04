#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D ourFace; 
uniform vec3 objColor; // 物体颜色
uniform vec3 ambientColor; // 环境光照

void main()
{
	// Fragcolor = vertexColor;
	// FragColor = texture(ourTexture, TexCoord) * texture(ourFace, TexCoord);
	FragColor = vec4(objColor * ambientColor, 1.0)* texture(ourTexture, TexCoord) * texture(ourFace, TexCoord);
}