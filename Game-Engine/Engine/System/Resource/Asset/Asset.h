#pragma once

#include "..\Object.h"

#include <vector>
#include <string>

class Asset : public Object
{
protected:
	std::vector<std::string> _filePaths;

public:
	std::string name;
	virtual ~Asset() {};
	virtual void Load(std::vector<std::string>& filePaths);

	std::vector<std::string> GetFilePaths();
	std::string GetName();
};

