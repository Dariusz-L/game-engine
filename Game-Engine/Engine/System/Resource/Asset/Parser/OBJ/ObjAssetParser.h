#pragma once

#include "..\AssetParser.h"
#include "..\..\..\..\Config\Include\IncludeAssimp.h"

#include <vector>

class ObjAssetParser : public AssetParser {

private:

//	std::vector<aiMesh*>* MeshesToVector(aiNode* node, const aiScene* scene, std::vector<aiMesh*>* meshes);

public:
	
	AssetParsed* Parse(AssetToParse* fileToParse) override;

};