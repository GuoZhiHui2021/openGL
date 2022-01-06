#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "render/shaderManager.h"
#include "render/def.h"
#include "common/coordinateType.h"
#include <system/systemManager.h>
#include "scene/world.h"

using namespace _Shader;
GLFWwindow* createWindow();
bool initGLAD();
void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

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
		
		ShaderManager::Instance()->initialize();

		glm::vec3 cubePositions[] = {
			  glm::vec3(0.0f,  0.0f,  0.0f),
			  glm::vec3(2.0f,  5.0f, -15.0f),
			  glm::vec3(-1.5f, -2.2f, -2.5f),
			  glm::vec3(-3.8f, -2.0f, -12.3f),
			  glm::vec3(2.4f, -0.4f, -3.5f),
			  glm::vec3(-1.7f,  3.0f, -7.5f),
			  glm::vec3(1.3f, -2.0f, -2.5f),
			  glm::vec3(1.5f,  2.0f, -2.5f),
			  glm::vec3(1.5f,  0.2f, -1.5f),
			  glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		SystemManager::Instance()->pushSystemCommand(SystemCommand(2, 1, "1"));
		for (size_t i = 0; i < 10; i++)
		{
			
			SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 1, std::to_string(i+1)));
			SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{" + std::to_string(i + 1) + ",1}"));
			SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{" + std::to_string(i + 1) + ",2}"));
			if(!(i%3))
				SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 2, "{" + std::to_string(i + 1) + ",10.0f,10.0f,0.0f}"));
			SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{" + std::to_string(i + 1) + "," + std::to_string(cubePositions[i].x) + "," + std::to_string(cubePositions[i].y) + "," + std::to_string(cubePositions[i].z) + "}"));
			//SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 4, "{1,0.0f,0.0f,0.0f}"));
			//SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 5, "{1,1.0f,1.0f,1.0f}"));
			//SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 1, "{1,true}"));
			//SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 2, "{1,material/default.materialPrototype}"));
		}

		//render.setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (!glfwWindowShouldClose(window))
		{
			//ÊäÈë
			processInput(window);
			//äÖÈ¾Ö¸Áî

			World::Instance()->tick();
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
		/*alpha = std::min(1.0f, std::max(0.0f, alpha + 0.01f));
		alpha_dirty = true;*/
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		/*alpha = std::min(1.0f, std::max(0.0f, alpha - 0.01f));
		alpha_dirty = true;*/
	}
}