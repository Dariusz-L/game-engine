#include "MaterialLoader.h"

#include "..\..\..\Resource\Asset\Parser\MTL\MtlAssetParsed.h"

void MaterialLoader::Load(Material* asset, AssetParsed* assetParsed) {

	MtlAssetParsed* mtlAssetParsed = static_cast<MtlAssetParsed*>(assetParsed);
}

void MaterialLoader::Destroy(Material* asset) {



}