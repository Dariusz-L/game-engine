#pragma once

#include "..\AssetParser.h"

class ShaderAssetParser : public AssetParser
{
public:
	AssetParsed* Parse(AssetToParse* fileToParse) override;
};

