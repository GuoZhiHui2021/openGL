#pragma once
#include <string>
#include <algorithm>
#include <filesystem>
#include <comdef.h>
std::string getAbsolutePath(const char* src);
std::string getAbsolutePath(std::string path);
std::string getWorkingDirectory();
bool isAbsolutePath(const char* src);
bool isAbsolutePath(std::string path);


std::string getAbsolutePath(const char* src)
{
	return getAbsolutePath(std::string(src));
}
std::string getAbsolutePath(std::string path)
{
	replace(path.begin(), path.end(), '/', '\\');
	char rp[127];
	sprintf_s(rp, "%s\\%s", getWorkingDirectory().c_str(), path.c_str());
	return  std::string(rp,strlen(rp));
}
std::string getWorkingDirectory()
{
	std::wstring path = std::filesystem::current_path().c_str();
	_bstr_t bstr(path.c_str());
	return std::string(bstr);
}

bool isAbsolutePath(const char* src)
{
	return isAbsolutePath(std::string(src));
}

bool isAbsolutePath(std::string path)
{
	replace(path.begin(), path.end(), '/', '\\');
	int p = -1;
	p = path.find(":\\", 0);
	return p >=0;
}
