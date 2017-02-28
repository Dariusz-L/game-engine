#pragma once

#include "..\AssetParser.h"

class MtlAssetParser : public AssetParser
{
public:
	AssetParsed* Parse(AssetToParse* fileToParse) override;
};

