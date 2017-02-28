#pragma once

#include "..\..\..\Resource\Asset\AssetLoader.h"

class Shader;

class ShaderLoader : public AssetLoader<Shader>
{
protected:
	void Load(Shader* asset, AssetParsed* assetParsed) override;
	void Destroy(Shader* asset) override;
};

