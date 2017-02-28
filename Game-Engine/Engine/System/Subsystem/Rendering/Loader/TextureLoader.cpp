#include "TextureLoader.h"

#include "..\..\..\Config\Include\IncludeOpenGL.h"

#include "..\..\..\Resource\ResourceData.h"
#include "..\..\..\Resource\Asset\AssetParsingManager.h"
#include "..\..\..\Resource\Asset\Parser\Image\ImageAssetParsed.h"
#include "..\Asset\Texture.h"

void TextureLoader::Load(Texture* tex, AssetParsed* assetParsed) {
		
	auto image = static_cast<ImageAssetParsed*>(assetParsed);

	tex->_width  = image->surface->w;
	tex->_height = image->surface->h;

	glGenTextures(1, &tex->_texture);
	glBindTexture(GL_TEXTURE_2D, tex->_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum inFormat	 = DeduceInputPixelsFormat	(image->surface);
	GLenum outFormat = DeduceOutputPixelsFormat	(image->surface);

	glTexImage2D(GL_TEXTURE_2D, 0, outFormat, 
		tex->_width, tex->_height, 0, inFormat, GL_UNSIGNED_BYTE, image->surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureLoader::Destroy(Texture* tex) {
	glDeleteTextures(1, &tex->_texture);
	tex->_texture = -1;
}

GLenum TextureLoader::DeduceInputPixelsFormat(SDL_Surface* surface)
{
	int r = surface->format->Rmask;
	int g = surface->format->Gmask;
	int b = surface->format->Bmask;
	int a = surface->format->Amask;

	int format = surface->format->BitsPerPixel;
#ifdef _MSC_VER
	if (r < g && g < b && format == 32)
		return GL_RGBA;
	if (b < g && g < r && format == 32)
		return GL_BGRA;
	if (r < g && g < b && format == 24)
		return GL_RGB;
	if (b < g && g < r && format == 24)
		return GL_BGR;
#else
	if (format == 32)
		return GL_RGBA;
	if (format == 24)
		return GL_RGB;
#endif
	return GL_RGBA;
}

GLenum TextureLoader::DeduceOutputPixelsFormat(SDL_Surface* surface)
{
	if (surface->format->BitsPerPixel == 32)
		return GL_RGBA;
	if (surface->format->BitsPerPixel == 24)
		return GL_RGB;

	return GL_RGBA;
}