#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace _Shader
{
	static unsigned int SHADER_TYPES[]{
		GL_VERTEX_SHADER,\
		GL_FRAGMENT_SHADER
	};
	const unsigned int VERTEXSHADER_TYPE = GL_VERTEX_SHADER;
	const unsigned int FRAGMENTSHADER_TYPE = GL_FRAGMENT_SHADER;
}
