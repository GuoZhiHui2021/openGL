#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord0;
out vec4 vertexColor;
out vec2 texCoord0;
uniform mat4 transform;
void main()
{
	gl_Position = transform * vec4(aPos.x,aPos.y,aPos.z,1.0f);
	vertexColor = vec4(aColor, 1.0);
	texCoord0 = aTexCoord0;
}
