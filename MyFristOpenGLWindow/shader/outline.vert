#version 330 core
layout (location = 0) in vec3 m_pos;
layout (location = 2) in vec3 m_normal;
layout (location = 3) in vec2 m_texCoord0;
layout (location = 4) in vec2 m_texCoord1;
layout (location = 5) in vec2 m_texCoord2;
layout (location = 6) in vec2 m_texCoord3;
layout (location = 7) in vec2 m_texCoord4;
layout (location = 8) in vec2 m_texCoord5;
layout (location = 9) in vec2 m_texCoord6;
layout (location = 10) in vec2 m_texCoord7;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform float outlineWidth;
uniform mat4 projectionMat;
out vec2 texCoord[8];
void main()
{
	vec3 n_normal = normalize(m_normal);
	gl_Position = projectionMat * viewMat * modelMat * vec4(m_pos.x + outlineWidth * n_normal.x,m_pos.y + outlineWidth * n_normal.y,m_pos.z + outlineWidth * n_normal.z,1.0f);
	texCoord[0] = m_texCoord0;
	texCoord[1] = m_texCoord1;
	texCoord[2] = m_texCoord2;
	texCoord[3] = m_texCoord3;
	texCoord[4] = m_texCoord4;
	texCoord[5] = m_texCoord5;
	texCoord[6] = m_texCoord6;
	texCoord[7] = m_texCoord7;
}
