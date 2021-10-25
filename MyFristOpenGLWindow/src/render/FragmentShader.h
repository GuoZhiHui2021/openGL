#pragma once
#include "render/Shader.h"
namespace _Shader {
	class FragmentShader :
		public Shader
	{
	public:
		FragmentShader(const GLchar* shaderSource);
		virtual ~FragmentShader()
		{
			Shader::~Shader();
		}
		virtual const unsigned int getShaderType() { return GL_FRAGMENT_SHADER; };
	};
}

