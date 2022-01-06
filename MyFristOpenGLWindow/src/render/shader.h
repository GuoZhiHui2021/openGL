#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
namespace _Shader
{
	class Shader
	{
	protected:
		unsigned int m_shaderID;
		GLchar* m_shaderCode;
		std::string m_shader;
		bool m_compile;
	public:
		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader(const GLchar * shaderSource,unsigned int shaderType);
		virtual ~Shader();
		void load(const GLchar * shaderSource, unsigned int shaderType);
		unsigned int getShaderID();
		const GLchar* getShaderCode();
		void deleteShader();
		bool compile();
		inline bool isCompile() { return m_compile; };
		std::string getShaderName() { return m_shader; };
		virtual const unsigned int getShaderType() = 0;
	};
}


