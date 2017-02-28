#pragma once

#include "..\..\Utility\Containers\Pool.h"
#include "..\Asset\Parser\AssetParsed.h"

#include <vector>

template<class ASSET_TYPE>
class ComponentLoader {

public:
	Pool<ASSET_TYPE>* CreatePool(std::vector<AssetParsed*>* assetsParsed) {
		auto pool = new Pool<ASSET_TYPE>();
		int poolSize = assetsParsed->size();
		pool->Init<ASSET_TYPE>(poolSize);

		for (int i = 0; i < poolSize - 1; i++) {
			ASSET_TYPE* a = pool->GetNext();
			Load(a, (*assetsParsed)[i]);
		}

		return pool;
	}
	
	virtual void Load(ASSET_TYPE* asset, AssetParsed* assetParsed) = 0;

};