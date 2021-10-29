#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include "render/ShaderManager.h"
#include "render/def.h"
#include "render/PanelRender.h"

using namespace _Shader;
GLFWwindow* createWindow();
TextureData createTextureData(const char* src, uint16_t textureUnit, uint16_t wrap_s = GL_REPEAT, uint16_t wrap_t = GL_REPEAT, uint16_t min_filter = GL_NEAREST, uint16_t max_filter = GL_NEAREST);
RenderData* createRenderData(int id, float* vertices, int count, unsigned int *indices, int element_count, TextureData* textureDatas, int texture_count);
bool initGLAD();
void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

float alpha = 0.5f;
bool alpha_dirty = true;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = createWindow();
	if (window == NULL)
		return -1;
	if (!initGLAD())
		return -1;
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
	{
		/*float vertices[] = {
			-0.8f, -0.4f,0.0f,  1.0f,0.0f,0.0f,    0.5f, 0.5f,
			-0.2f, -0.4f,0.0f,  0.0f,1.0f,0.0f,    1.5f, 0.5f,
			-0.2f, 0.4f, 0.0f,  1.0f,0.0f,0.0f,    1.5f, 1.5f,
			-0.8f, 0.4f, 0.0f,  0.0f,0.0f,1.0f,    0.5f, 1.5f,
			0.2f, -0.4f, 0.0f,  1.0f,0.0f,0.0f,    0.0f, 0.0f,
			0.8f, -0.4f, 0.0f,  0.0f,1.0f,0.0f,    1.0f, 0.0f,
			0.8f, 0.4f, 0.0f,   1.0f,0.0f,0.0f,     1.0f, 1.0f,
			0.2f, 0.4f, 0.0f,   0.0f,0.0f,1.0f,     0.0f, 1.0f,
		};*/
		
		float vertices[] = {
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f,
		};
		/*float vertices[] = {
			-0.8f, -0.4f,0.0f,  1.0f,0.0f,0.0f,
			-0.2f, -0.4f,0.0f,  0.0f,1.0f,0.0f,
			-0.2f, 0.4f, 0.0f,  1.0f,0.0f,0.0f, 
			-0.8f, 0.4f, 0.0f,  0.0f,0.0f,1.0f,  
			0.2f, -0.4f, 0.0f,  1.0f,0.0f,0.0f,   
			0.8f, -0.4f, 0.0f,  0.0f,1.0f,0.0f,  
			0.8f, 0.4f, 0.0f,   1.0f,0.0f,0.0f,  
			0.2f, 0.4f, 0.0f,   0.0f,0.0f,1.0f,  
		};*/
		/*unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3,
			4, 5, 7,
			5, 6, 7,
		};*/
		unsigned int indices[] = {
			0, 2, 1,
		};
		
		ShaderManager::Instance()->initialize();
		ShaderManager::Instance()->addShader(VERTEXSHADER_TYPE, "shader/shaders.vs");
		ShaderManager::Instance()->addShader(FRAGMENTSHADER_TYPE, "shader/shaders.fs");
		PanelRender render;
		render.initialize();
		render.attachShader(VERTEXSHADER_TYPE, "shader/shaders.vs");
		render.attachShader(FRAGMENTSHADER_TYPE, "shader/shaders.fs");
		render.initialized();

		RenderData* renderData = createRenderData(1, vertices, 3, indices, 3, NULL, 0);

		render.loadData(renderData);
		float rightOff = 0.3f;
		render.setUniform("rightOff", (void*)&rightOff, 1, ShaderParamType::SPT_FLOAT);
		//render.setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (!glfwWindowShouldClose(window))
		{
			// ‰»Î
			processInput(window);
			//‰÷»æ÷∏¡Ó
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			render.render();

			glfwPollEvents();
			glfwSwapBuffers(window);
		}
	}
	glfwTerminate();
	return 0;
}


GLFWwindow* createWindow()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnCreateWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	return window;
}
TextureData createTextureData(const char* src, uint16_t textureUnit, uint16_t wrap_s, uint16_t wrap_t, uint16_t min_filter, uint16_t max_filter)
{
	TextureData data;
	memcpy(&data.texture, src, strlen(src));
	data.texture[strlen(src)] = '\0';
	data.options[0] = wrap_s;
	data.options[1] = wrap_t;
	data.options[2] = min_filter;
	data.options[3] = max_filter;
	data.textureUnit = textureUnit;
	return data;
}
RenderData* createRenderData(int id,float* vertices, int count, unsigned int *indices, int element_count, TextureData* textureDatas,int texture_count)
{
	RenderData* renderData = new RenderData();
	renderData->vertices = (float*)malloc(count * 3 * sizeof(float));
	memcpy(renderData->vertices, vertices, count * 3 * sizeof(float));
	renderData->count = count;
	renderData->element = (unsigned int*)malloc(element_count * sizeof(float));
	memcpy(renderData->element, indices, element_count * sizeof(float));
	renderData->element_count = element_count;
	renderData->useColor = false;
	//renderData->useUV[0] = true;
	renderData->id = id;
	renderData->textures = new TextureData[texture_count];
	for (int i = 0; i < texture_count; i++)
	{
		TextureData& textureData = renderData->textures[i];
		memcpy(&textureData, &textureDatas[i], sizeof(TextureData));
	}
	renderData->textureSize = texture_count;
	return renderData;
}
bool initGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}
	return true;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		alpha = std::min(1.0f, std::max(0.0f, alpha + 0.01f));
		alpha_dirty = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		alpha = std::min(1.0f, std::max(0.0f, alpha - 0.01f));
		alpha_dirty = true;
	}
}