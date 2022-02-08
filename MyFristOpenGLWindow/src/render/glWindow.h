#pragma once
#include <unordered_map>
#define MOUSE_UP (GLFW_KEY_LAST + 1)
#define MOUSE_RIGHT (GLFW_KEY_LAST + 2)
#define MOUSE_SRCOLL (GLFW_KEY_LAST + 3)
#define WINDOW_WIDTH (GLFW_KEY_LAST + 4)
#define WINDOW_HEIGHT (GLFW_KEY_LAST + 5)

bool glInit();
int glWindowShouldClose();
void setWindowSize(int width,int height);
void glTerminate();
void glPollEvents();
void glSwapBuffers();
void recordInputEvent();
std::unordered_map<int, int> getInputEvent();
void clearInputEvent();