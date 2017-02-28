#pragma once

#include "..\AssetParsed.h"

#include "..\..\..\..\Config\Include\IncludeSDL.h"

struct ImageAssetParsed : AssetParsed {

	SDL_Surface* surface;

	~ImageAssetParsed() {
		SDL_FreeSurface(surface);
	}
};