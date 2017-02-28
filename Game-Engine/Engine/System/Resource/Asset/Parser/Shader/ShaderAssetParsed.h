#pragma once

#include "..\AssetParsed.h"

#include <string>

struct ShaderAssetParsed : AssetParsed {

	std::string vertexCode;
	std::string fragmentCode;

};