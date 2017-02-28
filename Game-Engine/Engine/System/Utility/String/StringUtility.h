#pragma once
#include <vector>
#include <string>

namespace Utility { namespace String {
	std::string Concat(std::string first, std::string second);
	std::vector<std::string> Split(std::string str, char delimiter);
	std::string GetStringFromBeetwenTwoChars(const std::string& str, const char first, const char second);
	bool IfContainStr(const std::string& inStr, const std::string& whatStr);
	std::string RemoveSubstring(const std::string& inStr, const std::string& subStr);
	float StringToFloat(const std::string& str);
	int StringToInt(const std::string& str);
	bool IsNumber(const std::string& str);
}}