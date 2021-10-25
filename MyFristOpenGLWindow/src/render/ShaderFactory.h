#pragma once
#include "render/Shader.h"
//#include "FragmentShader.h"
//#include "VertexShader.h"
#include <string>
namespace _Shader {
	using std::string;

	class ShaderFactory
	{
	public:
		virtual Shader* createShader(const string& name) = 0;
		virtual void destoryShader(Shader*) = 0;
	};

	template<class T>
	class TplShaderFactory:public ShaderFactory
	{
	public:
		TplShaderFactory();
		virtual Shader* createShader(const string& name);
		virtual void destoryShader(Shader*);
		//~TplShaderFactory() {}
		/*virtual Shader* createShader(const string& name);
		virtual void destoryShader(Shader*);*/
	};


	template<class T>
	TplShaderFactory<T>::TplShaderFactory()
	{
		static_assert(std::is_base_of<Shader, T>::value);
	}
	/*template<class T>
	TplShaderFactory<T>::TplShaderFactory():ShaderFactory()
	{
	}
*/
	template<class T>
	Shader * TplShaderFactory<T>::createShader(const string & name)
	{
		return new T(name.c_str());
	}

	template<class T>
	void TplShaderFactory<T>::destoryShader(Shader * shader)
	{
		shader->deleteShader();
		delete shader;
	}
}


