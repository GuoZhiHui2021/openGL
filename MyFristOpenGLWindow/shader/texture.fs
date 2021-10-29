#version 330 core
in vec4 vertexColor;
in vec2 texCoord0;
uniform vec4 outColor;
uniform sampler2D texture0;
uniform sampler2D texture1;
out vec4 FragColor;
void main()
{
	FragColor = mix(texture(texture0, texCoord0),texture(texture1, texCoord0),0.2);
}
