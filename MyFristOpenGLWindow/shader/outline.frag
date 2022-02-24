#version 330 core
in vec2 texCoord[8];
uniform vec3 outlineColor;
out vec4 FragColor;

void main()
{
	FragColor = vec4(outlineColor,1.0);
}