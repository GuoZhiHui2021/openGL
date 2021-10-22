#pragma once
#include "Shader.h"
namespace _Shader{
	class VertexShader :
		public Shader
	{
	public:
		VertexShader(const GLchar* shaderSource);
		virtual ~VertexShader()
		{
			Shader::~Shader();
		}
		virtual const unsigned int getShaderType() { return GL_VERTEX_SHADER; };
	};
}
