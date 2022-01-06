#pragma once
#include "render/shader.h"
#include <string>
#include <unordered_map>
namespace _Shader {
enum class ShaderParamType
{
	SPT_UNKNOWN = 0,
	SPT_INT,
	SPT_FLOAT,
	SPT_VEC2,
	SPT_VEC3,
	SPT_VEC4,
	SPT_MAT4,
	SPT_TEXTURE,
};
class ShaderProgram
{
	public:
		struct Uniform
		{
			std::string m_name = "UnKnown";
			int m_type = (int)ShaderParamType::SPT_UNKNOWN;
			int				m_count = -1;
			int				m_sizeInBytes = -1;
			int				m_location = -1;	
			uint8_t*		m_value = nullptr;
			bool			m_isDirty = true;

			Uniform() = default;
			Uniform(const Uniform&) = delete;
			Uniform(Uniform&&) = delete;
			Uniform& operator=(const Uniform&) = delete;
			Uniform& operator=(Uniform&&) = delete;
			// 析构函数
			~Uniform()
			{
				delete m_value;
			}

			// 重置当前值
			void setDirty()
			{
				m_isDirty = true;
			}

			// 设置值
			void setValue(const void* value, uint8_t count);
			void update(ShaderProgram* program);
		};
	private:
		unsigned int m_programID = 0;
		std::unordered_map<unsigned int, Shader*>  m_shader_map;
		std::unordered_map<std::string, Uniform*> m_unifroms;
	public:
		ShaderProgram();
		ShaderProgram(const ShaderProgram &) = delete;
		~ShaderProgram()
		{
			glDeleteProgram(m_programID);
		}
		void attach(Shader*);
		void detch(Shader*);
		void setUniform(const std::string &name, ShaderParamType pType, void* value, uint8_t count = 0);
		bool link();
		void use();
		void update();
		unsigned int getProgramID() const;
		static ShaderParamType convertToShaderParamType(uint16_t type)
		{
			switch (type)
			{
			case GL_INT: return ShaderParamType::SPT_INT;
			case GL_FLOAT: return ShaderParamType::SPT_FLOAT;
			case GL_FLOAT_VEC2: return ShaderParamType::SPT_VEC2;
			case GL_FLOAT_VEC3: return ShaderParamType::SPT_VEC3;
			case GL_FLOAT_VEC4: return ShaderParamType::SPT_VEC4;
			case GL_FLOAT_MAT4: return ShaderParamType::SPT_MAT4;
			case GL_TEXTURE0:
			case GL_TEXTURE1:
			case GL_TEXTURE2:
			case GL_TEXTURE3:
			case GL_TEXTURE4:
			case GL_TEXTURE5:
			case GL_TEXTURE6:
			case GL_TEXTURE7:return ShaderParamType::SPT_TEXTURE;
			default:
				return ShaderParamType::SPT_UNKNOWN;
			}
		}
	};
}


