#pragma once
#include "Shader.h"
#include <string>
#include <unordered_map>
namespace _Shader {
enum ShaderParamType
{
	SPT_UNKNOWN,
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
			ShaderParamType m_type = SPT_UNKNOWN;
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
		void setUniform(const std::string &name, void* value, uint8_t count, ShaderParamType pType);
		bool link();
		void use();
		unsigned int getProgramID() const;
	};
}


