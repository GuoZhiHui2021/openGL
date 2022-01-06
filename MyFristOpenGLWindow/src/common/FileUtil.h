#pragma once
#include <string>
#include <algorithm>
#include <filesystem>
#include <comdef.h>
#include <vector>
#include <io.h>
#include <iostream>
#include <fstream>
std::string getAbsolutePath(const char* src);
std::string getAbsolutePath(std::string path);
std::string getWorkingDirectory();
bool isAbsolutePath(const char* src);
bool isAbsolutePath(std::string path);
std::vector<std::string> readLines(std::string path);
std::vector<std::string> splitStr(std::string src, std::string delimiters);
std::vector<std::string> splitLevelStr(std::string src, std::string delimiters);




