#version 330 core
in vec4 vertexColor;
in vec2 texCoord0;
uniform sampler2D diffuse0;
out vec4 FragColor;
void main()
{
	FragColor = texture(diffuse0, texCoord0);
}
