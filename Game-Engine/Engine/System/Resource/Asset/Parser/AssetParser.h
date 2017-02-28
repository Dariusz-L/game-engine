#pragma once

#include <sstream>

struct AssetToParse;
struct AssetParsed;

class AssetParser {

public:

	virtual ~AssetParser () {}
	virtual AssetParsed* Parse(AssetToParse* fileToParse) = 0;

};