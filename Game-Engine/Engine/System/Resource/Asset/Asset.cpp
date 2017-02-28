#include "Asset.h"
#include "..\..\Utility\String\StringUtility.h"

void Asset::Load(std::vector<std::string>& filePaths)
{
	_filePaths = filePaths;
	std::vector<std::string> splitted = Utility::String::Split(filePaths[0], '/');
	name = Utility::String::Split(splitted[splitted.size() - 1], '.')[0];
}

std::vector<std::string> Asset::GetFilePaths()
{
	return _filePaths;
}

std::string Asset::GetName()
{
	return name;
}