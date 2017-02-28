#pragma once

#include "..\..\..\Config\Include\IncludeOpenGL.h"
#include "..\..\..\Config\Include\IncludeSDL.h"

#include "..\..\..\Resource\Asset\Asset.h"

#include <vector>

class Texture :
	public Asset
{
private:

	GLenum DeduceInputPixelsFormat(SDL_Surface* surface);
	GLenum DeduceOutputPixelsFormat(SDL_Surface* surface);

public:
	GLuint _texture;
	int _width;
	int _height;
	Texture();
	~Texture();
	void Load(std::vector<std::string>& filePaths) override;

	GLuint GetTexture();
};

