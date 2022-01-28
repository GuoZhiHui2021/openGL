#pragma once
#include <unordered_map>
#define MOUSE_UP (GLFW_KEY_LAST + 1)
#define MOUSE_RIGHT (GLFW_KEY_LAST + 2)

bool glInit();
int glWindowShouldClose();
void setWindowSize(int width,int height);
void setWindowSizeCallBack(void* (*callback)(int,int));
void glTerminate();
void glPollEvents();
void glSwapBuffers();
void recordInputEvent();
std::unordered_map<int, int> getInputEvent();
void clearInputEvent();