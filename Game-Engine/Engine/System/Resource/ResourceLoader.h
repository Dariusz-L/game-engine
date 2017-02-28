#pragma once

#include "Asset\AssetParsingManager.h"
#include "ResourceData.h"

class ResourceLoader
{
private:
	AssetParsingManager  _assetParsingManager;
	ResourceData _resources;

public:
	void ParseAllAssets();
	void UnparseAllAssets();

	AssetParsingManager*	GetAssetParsingManager();
	ResourceData*			GetAllResources();
};