#version 330 core
layout (location = 0) in vec3 aPos;
uniform float rightOff;
out vec4 vertexColor;
void main()
{
	gl_Position = vec4(aPos.x + rightOff,0.0 - aPos.y,aPos.z,1.0f);
	vertexColor = gl_Position;
}
