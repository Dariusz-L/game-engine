#pragma once

#include "..\..\..\Config\Include\IncludeOpenGL.h"
#include "..\..\..\Config\Include\IncludeSDL.h"

#include "..\..\..\Resource\Asset\AssetLoader.h"

class Texture;

class TextureLoader : public AssetLoader<Texture>
{
private:
	GLenum DeduceInputPixelsFormat(SDL_Surface* surface);
	GLenum DeduceOutputPixelsFormat(SDL_Surface* surface);

protected:
	void Load(Texture* asset, AssetParsed* assetParsed) override;
	void Destroy(Texture* asset) override;
};

