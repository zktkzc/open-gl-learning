#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D ourFace; 
uniform vec3 objColor; // ������ɫ
uniform vec3 ambientColor; // ��������

void main()
{
	// Fragcolor = vertexColor;
	// FragColor = texture(ourTexture, TexCoord) * texture(ourFace, TexCoord);
	FragColor = vec4(objColor * ambientColor, 1.0)* texture(ourTexture, TexCoord) * texture(ourFace, TexCoord);
}