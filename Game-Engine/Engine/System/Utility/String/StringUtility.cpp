#include "StringUtility.h"

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdarg>

namespace Utility { namespace String {

	std::string Concat(std::string first, std::string second) {
		return first + second;
	}

	std::vector<std::string> Split(std::string str, char delimiter) {
		std::vector<std::string> internal;
		std::stringstream ss(str);
		std::string tok;

		while (std::getline(ss, tok, delimiter))
		{
			internal.push_back(tok);
		}

		return internal;
	}

	std::string GetStringFromBeetwenTwoChars(const std::string& str, const char first, const char second) {
		std::string result;
		int size = str.size();
		bool write = false;
		for (int i = 0; i < size; i++) {
			if (result[i] == first)
				break;

			if (write)
				result += str[i];

			if (result[i] == second)
				write = true;

		}

		return result;
	}

	bool IfContainStr(const std::string& inStr, const std::string& whatStr) {
		if (inStr.find(whatStr) != std::string::npos)
			return true;
		else
			return false;
	}

	std::string RemoveSubstring(const std::string& inStr, const std::string& subStr) {
		std::string result = inStr;

		std::string::size_type i = result.find(subStr);

		if (i != std::string::npos)
			result.erase(i, subStr.length());

		return result;
	}

	float StringToFloat(const std::string& str) {
		return std::stof(str);
	}

	int StringToInt(const std::string& str) {
		return std::stoi(str);
	}

	bool IsNumber(const std::string& str) {
		for (char c : str) {
			if ((c < '0' || c > '9') && (c != '.' || c != ','))
				return false;
		}
	
		return true;
	}

}}