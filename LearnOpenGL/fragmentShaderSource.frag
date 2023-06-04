#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D ourFace;

void main()
{
	// Fragcolor = vertexColor;
	FragColor = texture(ourTexture, TexCoord) * texture(ourFace, TexCoord);
}