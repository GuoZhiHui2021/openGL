#include <render/glWindow.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "render/shaderManager.h"
#include "render/def.h"
#include "common/coordinateType.h"
#include <system/systemManager.h>
#include "scene/world.h"

using namespace _Shader;
void processInput(GLFWwindow*);

int main()
{
	glInit();
	{
		
		ShaderManager::Instance()->initialize();

		//render.setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		SystemManager::Instance()->pushSystemCommand(SystemCommand(2, 1, "1"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 1, "1"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{1,1}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{1,2}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 2, "{1,10.0f,10.0f,0.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{1,0.0f,0.0f,0.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 4, "{1,0.0f,45.0f,0.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 5, "{1,3.0f,1.0f,1.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 1, "{1,true}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 2, "{1,material/default.materialPrototype}"));

		SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 1, "2"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{2,1}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{2,2}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{2,3}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 2, "{2,10.0f,10.0f,0.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{2,2.0f,0.0f,-5.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 4, "{2,0.0f,45.0f,0.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 5, "{2,1.0f,1.0f,1.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 1, "{2,true}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 2, "{2,material/default.materialPrototype}"));

		SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 2, "3"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{3,1}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{3,0.0f,0.0f,10.0f}"));


		//SystemManager::Instance()->pushSystemCommand(SystemCommand(5, 1, "{1,2}"));
		while (!glWindowShouldClose())
		{
			//ÊäÈë
			//processInput(window);
			recordInputEvent();
			//äÖÈ¾Ö¸Áî
			
			World::Instance()->tick();
			glPollEvents();
			glSwapBuffers();
		}
	}
	glTerminate();
	return 0;
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
	//float cameraSpeed = 0.05f; // adjust accordingly
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	cameraPos += cameraSpeed * cameraFront;
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	cameraPos -= cameraSpeed * cameraFront;
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}