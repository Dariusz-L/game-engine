#pragma once
#include "..\System\Resource\Asset\Asset.h"
#include <string>
#include <unordered_map>

struct ResourceInfo
{
	std::unordered_map<int, Asset*>* resourcesMap;
	std::string folderPath;
	std::vector<std::string> filesPaths;

	ResourceInfo(
		std::unordered_map<int, Asset*>* resourcesMap_,
		const std::string& folderPath_,
		std::vector<std::string> filesPaths_)
	{
		resourcesMap = resourcesMap_;
		folderPath = folderPath_;
		filesPaths = filesPaths_;
	}
};