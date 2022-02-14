#version 330 core
in vec4 vertexColor;
in vec2 texCoord0;
uniform sampler2D surfaceColor;
out vec4 FragColor;
void main()
{
	FragColor = texture(surfaceColor, texCoord0);
}
