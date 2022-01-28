#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glWindow.h"
#include <iostream>
#include "def.h"

static GLFWwindow* glWnd = nullptr;
static bool isInited = false;
static int wndWidth = DEFAULT_Window_WIDTH;
static int wndHeight = DEFAULT_Window_HEIGHT;
static float scaleX = 1;
static float scaleY = 1;
static void* (*sizeCallBack)(int, int) ;
static std::unordered_map<int, int> events;


GLFWwindow* createWindow();
bool initGLAD();
void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow*);

bool glInit()
{
	if (isInited)
		return false;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = createWindow();
	if (window == NULL)
		return false;
	if (!initGLAD())
		return false;
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glWnd = window;
	return true;
}

int glWindowShouldClose()
{
	return glfwWindowShouldClose(glWnd);
}

void setWindowSize(int width, int height)
{
	_ASSERT(glWnd && width > 0 && height > 0);
	wndWidth = width;
	wndHeight = height;
	glfwSetWindowSize(glWnd, wndWidth, wndHeight);
}

void setWindowSizeCallBack(void* (*callback)(int, int))
{
	sizeCallBack = callback;
}

void glTerminate()
{
	glfwTerminate();
}

void glPollEvents()
{
	glfwPollEvents();
}

void glSwapBuffers()
{
	if(glWnd)
		glfwSwapBuffers(glWnd);
}

void recordInputEvent()
{
	if (glfwGetKey(glWnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(glWnd, true);
	}
	if (glfwGetKey(glWnd, GLFW_KEY_W) == GLFW_PRESS)
	{
		events[GLFW_KEY_W]++;
	}
	if (glfwGetKey(glWnd, GLFW_KEY_S) == GLFW_PRESS)
	{
		events[GLFW_KEY_S]++;
	}
	if (glfwGetKey(glWnd, GLFW_KEY_A) == GLFW_PRESS)
	{
		events[GLFW_KEY_A]++;
	}
	if (glfwGetKey(glWnd, GLFW_KEY_D) == GLFW_PRESS)
	{
		events[GLFW_KEY_D]++;
	}
}

std::unordered_map<int, int> getInputEvent()
{
	return events;
}

void clearInputEvent()
{
	events.clear();
}

GLFWwindow* createWindow()
{
	GLFWwindow* window = glfwCreateWindow(wndWidth, wndHeight, "LearnCreateWindow", NULL, NULL);
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
	scaleX = ((float)width) / DEFAULT_Window_WIDTH;
	scaleY = ((float)height) / DEFAULT_Window_HEIGHT;
	if (sizeCallBack)
	{
		sizeCallBack(width, height);
	}

	//glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static double lastX = DEFAULT_Window_WIDTH * 0.5;
	static double lastY = DEFAULT_Window_HEIGHT * 0.5;
	double offsetX = xpos - lastX;
	double offsetY = lastY - ypos;
	lastX = offsetX + lastX;
	lastY = offsetY + lastY;
	events[MOUSE_UP] += (int)(offsetY * 1000);
	events[MOUSE_RIGHT] += (int)(offsetX * 1000);
}
