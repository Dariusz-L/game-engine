#pragma once

#include "..\..\..\Resource\Asset\AssetLoader.h"

class Material;

class MaterialLoader : public AssetLoader<Material>
{
protected:
	void Load(Material* asset, AssetParsed* assetParsed) override;
	void Destroy(Material* asset) override;
};

