#pragma once

#include "..\..\..\Resource\Asset\AssetLoader.h"

class Mesh;

class MeshLoader : public AssetLoader<Mesh> {
public:
	void Load(Mesh* asset, AssetParsed* assetParsed) override;
	void Destroy(Mesh* asset) override;
};

