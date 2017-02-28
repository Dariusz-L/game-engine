#pragma once

#include "..\Asset\Parser\AssetParsed.h"

#include "SpecificAssets.h"

#include <vector>

template<class ASSET_TYPE>
class AssetLoader {

public:
	virtual ~AssetLoader() {};

	SpecificAssets* LoadAssets(std::vector<AssetParsed*>* assetsParsed) {
		auto assets = new SpecificAssets();
		int size = assetsParsed->size();

		for (int i = 0; i < size; i++) {
			auto assetParsed = (*assetsParsed)[i];
			auto asset = new ASSET_TYPE();
			asset->SetID(i);
			asset->name = assetParsed->name;
			Load(asset, assetParsed);
			assets->emplace(i, asset);
		}

		return assets;
	}
	
	void DestroyAssets(SpecificAssets* assets) {
		for (auto a : *assets) {
			Asset* asset = a.second;
			Destroy(static_cast<ASSET_TYPE*>(asset));
			delete asset;
		}

		delete assets;
	}

protected:
	virtual void Load	(ASSET_TYPE* asset, AssetParsed* assetParsed) = 0;
	virtual void Destroy(ASSET_TYPE* asset) = 0;
};