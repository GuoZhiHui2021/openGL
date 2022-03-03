#include <render/glWindow.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "render/shaderManager.h"
#include "render/def.h"
#include "common/coordinateType.h"
#include <system/systemManager.h>
#include "scene/world.h"
#include "render/meshManager.h"

using namespace _Shader;

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
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 5, "{1,3.0f,2.0f,2.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 1, "{1,true}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 2, "{1,material/phong.materialPrototype}"));

		SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 1, "2"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{2,1}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{2,2}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 2, "{2,10.0f,10.0f,0.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{2,2.0f,0.0f,-5.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 4, "{2,0.0f,45.0f,0.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 5, "{2,1.0f,1.0f,1.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 1, "{2,true}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 2, "{2,material/boxPhong.material}"));

		//摄像机
		SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 2, "3"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{3,1}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{3,0.0f,0.0f,10.0f}"));

		//光照
		SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 1, "4"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{4,1}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{4,2}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{4,3}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{4,4.0f,3.0f,-5.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 5, "{4,0.3f,0.3f,0.3f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(10, 16, "{4,0.8f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(10, 6, "{4,0.5f,0.3f,0.7f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(10, 7, "{4,0.5f,0.3f,0.7f}"));

		SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 1, "5"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{5,1}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{5,2}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{5,4}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{5,1.0f,0.0f,-2.5f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 5, "{5,0.3f,0.3f,0.3f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(10, 17, "{5,0.5f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(10, 6, "{5,0.6f,0.3f,0.7f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(10, 7, "{5,1.0f,0.3f,0.7f}"));

		SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 1, "6"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{6,1}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{6,2}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{6,5}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{6,0.0f,0.0f,6.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 4, "{6,0.0f,180.0f,0.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 5, "{6,0.3f,0.3f,0.3f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(10, 18, "{6,0.5f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(10, 15, "{6,2.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(10, 12, "{6,0.4f,0.8f,0.2f}"));

		//模型
		SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 1, "7"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{7,1}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{7,2}"));
		//SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 2, "{2,10.0f,10.0f,0.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{7,0.0f,-1.0f,2.3f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 5, "{7,0.2f,0.2f,0.2f}"));
		//SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 2, "{7,material/phong.materialPrototype}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 3, "{7,res/mesh/nanosuit/nanosuit.obj}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 4, "{7,true}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 5, "{7,0.2,0.3,0.5}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 6, "{7,0.2}"));
		//SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 4, "{2,0.0f,45.0f,0.0f}"));
		//SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 5, "{2,1.0f,1.0f,1.0f}"));
	/*	SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 1, "{2,true}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 2, "{2,material/boxPhong.material}"));*/

		//Plane
		SystemManager::Instance()->pushSystemCommand(SystemCommand(3, 1, "8"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{8,1}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(4, 1, "{8,2}"));
		//SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 2, "{2,10.0f,10.0f,0.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 3, "{8,0.0f,-1.0f,3.0f}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(6, 4, "{8,90.0f,0.0f,0.0f}"));
		//SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 2, "{7,material/phong.materialPrototype}"));
		SystemManager::Instance()->pushSystemCommand(SystemCommand(7, 3, "{8,Plane}"));

		while (!glWindowShouldClose())
		{
			//输入
			recordInputEvent();
			//渲染指令
			
			World::Instance()->tick();
			glPollEvents();
			glSwapBuffers();
		}
	}
	glTerminate();
	return 0;
}
