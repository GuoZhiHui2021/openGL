#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace _Shader
{
#define DEFAULT_Window_WIDTH 800
#define DEFAULT_Window_HEIGHT 600
#define DEFAULT_CAMERA_VEIW_X 0
#define DEFAULT_CAMERA_VEIW_Y 0
#define DEFAULT_CAMERA_VEIW_X_OFFSET 800
#define DEFAULT_CAMERA_VEIW_Y_OFFSET 600

	static unsigned int SHADER_TYPES[]{
		GL_VERTEX_SHADER,\
		GL_FRAGMENT_SHADER
	};
	const unsigned int VERTEXSHADER_TYPE = GL_VERTEX_SHADER;
	const unsigned int FRAGMENTSHADER_TYPE = GL_FRAGMENT_SHADER;


}
