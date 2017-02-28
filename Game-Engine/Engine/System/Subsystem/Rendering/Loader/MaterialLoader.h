#pragma once

#include "..\..\..\Resource\Asset\AssetLoader.h"

class MtlMaterial;

class MaterialLoader : public AssetLoader<MtlMaterial>
{
protected:
	void Load(MtlMaterial* asset, AssetParsed* assetParsed) override;
	void Destroy(MtlMaterial* asset) override;
};

