#pragma once

#include "..\AssetParser.h"

class ImageAssetParser : public AssetParser
{
public:
	AssetParsed* Parse(AssetToParse* fileToParse) override;
};

