#include "Texture.h"
#include "..\..\..\..\Loader\FileLoader.h"

#include <vector>

Texture::Texture()
{
	_texture = -1;
}

Texture::~Texture()
{
	glDeleteTextures(1, &_texture);
	_texture = -1;
}

void Texture::Load(std::vector<std::string>& filePaths)
{
	Asset::Load(filePaths);

	SDL_Surface* surface = FileLoader::LoadImageFile(filePaths[0]);

	std::string message("");
	if (surface == NULL)
		message = filePaths[0] + " failed to load";
	else
		message = filePaths[0] + " successfully loaded";
	SDL_Log("%s", message.c_str());

	_width = surface->w;
	_height = surface->h;

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum inFormat = DeduceInputPixelsFormat(surface);
	GLenum outFormat = DeduceOutputPixelsFormat(surface);

	glTexImage2D(GL_TEXTURE_2D, 0, outFormat, _width, _height, 0, inFormat, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(surface);
}

GLenum Texture::DeduceInputPixelsFormat(SDL_Surface* surface)
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

GLenum Texture::DeduceOutputPixelsFormat(SDL_Surface* surface)
{
	if (surface->format->BitsPerPixel == 32)
		return GL_RGBA;
	if (surface->format->BitsPerPixel == 24)
		return GL_RGB;

	return GL_RGBA;
}

GLuint Texture::GetTexture()
{
	return _texture;
}
