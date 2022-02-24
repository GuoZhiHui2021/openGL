#include "util.h"
#include "fileUtil.h"
bool getBoolValue(std::string str, int64_t& id, bool& value)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 2)
		return false;
	int64_t t_id = 0;
	bool t_value;
	if (!strToInt64(strs[0].c_str(), t_id))
		return false;
	if (!strToBool(strs[1].c_str(), t_value))
		return false;
	id = t_id;
	value = t_value;
	return true;
}

bool getFloatValue(std::string str, int64_t& id, float& value)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 2)
		return false;
	int64_t t_id = 0;
	float t_value = 0;
	if (!strToInt64(strs[0].c_str(), t_id) || !strToFloat(strs[1].c_str(), t_value))
		return false;
	id = t_id;
	value = t_value;
	return true;
}

bool getV3Value(std::string str, int64_t& id, std::vector<float>& value)
{
	value.clear();
	value.resize(3, 0);
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 4)
		return false;
	int64_t t_id = 0;
	std::vector<float> t_value(3, 0);
	if (!strToInt64(strs[0].c_str(), t_id))
		return false;
	for (size_t i = 1; i < 4; i++)
	{
		if (!strToFloat(strs[i].c_str(), t_value[i - 1]))
			return false;
	}
	id = t_id;
	value.swap(t_value);
	return true;
}


bool getStringValue(std::string str, int64_t& id, std::string& value)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 2)
		return false;
	int64_t t_id = 0;
	if (!strToInt64(strs[0].c_str(), t_id))
		return false;
	id = t_id;
	value = strs[1];
	return true;
}

bool getInt64Value(std::string str, int64_t& id, int64_t& value)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 2)
		return false;
	int64_t t_id = 0;
	int64_t t_value = 0;
	if (!strToInt64(strs[0].c_str(), t_id) || !strToInt64(strs[1].c_str(), t_value))
		return false;
	id = t_id;
	value = t_value;
	return id > 0 && value > 0;
}

bool getIntValue(std::string str, int64_t& id, int& value)
{
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 2)
		return false;
	int64_t t_id = 0;
	int t_value = 0;
	if (!strToInt64(strs[0].c_str(), t_id) || !strToInt(strs[1].c_str(), t_value))
		return false;
	id = t_id;
	value = t_value;
	return id > 0 && value > 0 && id != value;
}

bool getIntV2Value(std::string str, int64_t& id, std::vector<int>& value)
{
	value.clear();
	value.resize(2, 0);
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 3)
		return false;
	int64_t t_id = 0;
	std::vector<int> t_value(2, 0);
	if (!strToInt64(strs[0].c_str(), t_id))
		return false;
	for (size_t i = 1; i < 3; i++)
	{
		if (!strToInt(strs[i].c_str(), t_value[i - 1]))
			return false;
	}
	id = t_id;
	value.swap(t_value);
	return true;
}

bool getV2Value(std::string str, int64_t& id, std::vector<float>& value)
{
	value.clear();
	value.resize(2, 0);
	auto strs = splitLevelStr(str.substr(1, str.length() - 2), ",");
	if (strs.size() != 3)
		return false;
	int64_t t_id = 0;
	std::vector<float> t_value(2, 0);
	if (!strToInt64(strs[0].c_str(), t_id))
		return false;
	for (size_t i = 1; i < 3; i++)
	{
		if (!strToFloat(strs[i].c_str(), t_value[i - 1]))
			return false;
	}
	id = t_id;
	value.swap(t_value);
	return true;
}

