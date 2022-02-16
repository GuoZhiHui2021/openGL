#version 330 core
in vec4 vertexColor;
in vec2 texCoord0;
uniform vec3 lightColor;
out vec4 FragColor;
void main()
{
	FragColor = vec4(lightColor, 1);
}
