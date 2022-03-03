#pragma once
#include <stdint.h>
#include <chrono>
#include <cstring>
#include <string>
#include <math.h>
#include <vector>

#define PI acos(-1)

static double angleToRadian(double ang)
{
	int flag = ang < 0 ? -1 : 1;
	ang *= flag;
	ang = fmod(ang, 360.0);
	if (ang > 180)
	{
		ang = ang - 360.0;
	}
	ang *= flag;
	return ang / 180 * PI;
}

static double radianToAngle(double rad)
{
	int flag = rad < 0 ? -1 : 1;
	rad *= flag;
	rad = fmod(rad, 2 * PI);
	if (rad > PI)
	{
		rad = rad - 2 *PI;
	}
	rad *= flag;
	return rad / PI * 180;
}

static void removeHTSpaces(std::string& s)
{
	if (!s.empty())
	{
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}
}

static bool isInt(const char* str)
{
	bool isNum = false;

	int index = 0;
	for (; *str != '\0'; str++, index++)
	{
		switch (*str)
		{
		case '0':case'1':case'2':case'3':case'4':case'5':
		case'6':case'7':case'8':case'9':
			isNum = true;
			break;
		case '-':case '+':
			if (index != 0)
			{
				return false;
			}
			break;
		default:
			return false;
		}
	}

	if (!isNum)
	{
		return false;
	}

	return true;
}

static bool isFloat(const char* str)
{
	bool isE = false,
		isF = false,
		isPoint = false,
		numBefore = false,
		numBehind = false;

	int index = 0;
	for (; *str != '\0'; str++, index++)
	{
		if (isF)
			return false;
		switch (*str)
		{
		case '0':case'1':case'2':case'3':case'4':case'5':
		case'6':case'7':case'8':case'9':
			if (isE)
			{
				numBehind = true;
			}
			else
			{
				numBefore = true;
			}
			break;
		case '+':case '-':
			if (index != 0)
			{
				return false;
			}
			break;
		case 'e':case 'E':
			if (isE || !numBefore)
			{
				return false;
			}
			else
			{
				isPoint = true;
				index = -1;
				isE = true;
			}
			break;
		case '.':
			if (isPoint)
			{
				return false;
			}
			else
			{
				isPoint = true;
			}
			break;
		case 'f':case 'F':
			isF = true;
			break;
		default:
			return false;
		}
	}

	if (!numBefore)
	{
		return false;
	}
	else if (isE && !numBehind)
	{
		return false;
	}

	return true;
}


static int64_t allocateId()
{
	static int64_t index = 1;
	static int64_t lastTime = 0;
	static int64_t runtimeId = 1;
	int64_t time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	index = lastTime == time ? index + 1 : 1;
	lastTime = time;
	int64_t id = (time << 14) | index;
	return id;
}
static bool strToRGBA(const char* src, uint32_t& ret)
{
	std::string s(src);
	removeHTSpaces(s);

	if (strlen(s.c_str()) != 10|| s[0]!='0'||(s[1] != 'x'&& s[1] != 'X'))
		return false;
	for (int i = 2; i < 10; i++)
	{
		if (!isxdigit(s[i]))
			return false;
	}
	//char* c = const_cast<char*>(src);
	ret = (uint32_t)strtoll(s.c_str(),nullptr,0);
	return true;
}
static bool strToInt(const char* src, int32_t& ret)
{
	std::string s(src);
	removeHTSpaces(s);
	if (!isInt(s.c_str()))
		return false;
	int32_t i = std::stoi(s.c_str());
	ret = i;
	return true;
}
static bool strToUInt(const char* src, unsigned int& ret)
{
	std::string s(src);
	removeHTSpaces(s);
	if (!isInt(s.c_str()))
		return false;
	unsigned int i = std::strtoul(s.c_str(),NULL,10);
	ret = i;
	return true;
}
static bool strToInt64(const char* src, int64_t& ret)
{
	std::string s(src);
	removeHTSpaces(s);
	if (!isInt(s.c_str()))
		return false;
	int64_t i = std::stoll(s.c_str());
	ret = i;
	return true;
}
static bool strToFloat(const char* src, float_t& ret)
{
	std::string s(src);
	removeHTSpaces(s);
	if (!isFloat(s.c_str()))
		return false;
	float_t f = std::stof(s.c_str());;
	ret = f;
	return true;
}
static bool strToBool(const char* src, bool& ret)
{
	std::string s(src);
	removeHTSpaces(s);
	if (s == "false")
	{
		ret = false;
		return true;
	}
	else if (s == "true")
	{
		ret = true;
		return true;
	}
	return false;
}

bool getStringValue(std::string str, int64_t& id, std::string& value);

bool getV3Value(std::string str, int64_t& id, std::vector<float>& value);

bool getBoolValue(std::string str, int64_t& id, bool& value);

bool getFloatValue(std::string str, int64_t& id, float& value);

bool getInt64Value(std::string str, int64_t& id, int64_t& value);

bool getIntValue(std::string str, int64_t& id, int& value);

bool getIntV2Value(std::string str, int64_t& id, std::vector<int>& value);

bool getV2Value(std::string str, int64_t& id, std::vector<float>& value);

bool getUIntValue(std::string str, int64_t& id, unsigned int& value);