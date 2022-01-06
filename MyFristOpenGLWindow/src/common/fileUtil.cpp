#include "fileUtil.h"

std::string getAbsolutePath(const char* src)
{
	return getAbsolutePath(std::string(src));
}
std::string getAbsolutePath(std::string path)
{
	replace(path.begin(), path.end(), '/', '\\');
	char rp[127];
	sprintf_s(rp, "%s\\%s", getWorkingDirectory().c_str(), path.c_str());
	return  std::string(rp, strlen(rp));
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
	return p >= 0;
}

std::vector<std::string> readLines(std::string path)
{
	std::vector<std::string> ret;
	const char* c_path = path.c_str();
	std::ifstream inFile(c_path, std::ios::in);
	if (!inFile) return ret;
	char c_str[127];
	while (inFile.getline(c_str, 127))
	{
		ret.emplace_back(c_str, strlen(c_str));
	}
	inFile.close();
	return ret;
}

std::vector<std::string> splitStr(std::string src, std::string delimiters)
{
	std::vector<std::string> ret;
	char* c_src = (char*)src.c_str();
	char* c_delimiters = (char*)delimiters.c_str();
	char* temp = strtok_s(c_src, c_delimiters, &c_src);
	while (temp)
	{
		ret.emplace_back(temp, strlen(temp));
		temp = strtok_s(c_src, c_delimiters, &c_src);
	}
	return ret;
}

std::vector<std::string> splitLevelStr(std::string src, std::string delimiters)
{
	std::vector<std::string> ret;
	if (delimiters == "{" || delimiters == "}")
		return ret;
	int cur = 0;
	while (cur < src.length())
	{
		int l_pos = src.find('{', cur);
		int d_pos = src.find(delimiters, cur);
		if (d_pos == std::string::npos)
		{
			if (src[src.length() - 1] == '}')
			{
				ret.clear();
				break;
			}
			ret.push_back(src.substr(cur, src.length() - cur));
			cur = src.length();
		}
		else if (l_pos == std::string::npos || d_pos < l_pos)
		{
			if (src[d_pos - 1] == '}')
			{
				ret.clear();
				break;
			}
			ret.push_back(src.substr(cur, d_pos - cur));
			cur = d_pos + 1;
		}
		else if (d_pos > l_pos)
		{
			int curLevel = 1;
			int r_pos = src.find('}', l_pos + 1);
			while ((curLevel > 0 && r_pos != std::string::npos) || (r_pos != std::string::npos && r_pos < d_pos))
			{
				auto tl_pos = src.find('{', l_pos + 1);
				if (tl_pos != std::string::npos && tl_pos < r_pos)
				{
					curLevel++;
					l_pos = tl_pos;
				}
				else
				{
					d_pos = src.find(delimiters, r_pos + 1);
					if (d_pos == std::string::npos)
						d_pos = src.length();
					r_pos = src.find("}", r_pos + 1);
					curLevel--;
				}
			}
			if (curLevel == 0)
			{
				ret.push_back(src.substr(cur, d_pos - cur));
				cur = d_pos + 1;
			}
			else
			{
				ret.clear();
				break;
			}
		}
	}
	return ret;
}
