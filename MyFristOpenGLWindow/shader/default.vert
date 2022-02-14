#version 330 core
layout (location = 0) in vec3 m_pos;
layout (location = 3) in vec3 m_normal;
layout (location = 4) in vec2 m_texCoord0;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;
out vec2 texCoord0;
void main()
{
	gl_Position = projectionMat * viewMat * modelMat * vec4(m_pos.x,m_pos.y,m_pos.z,1.0f);
	texCoord0 = m_texCoord0;
}
