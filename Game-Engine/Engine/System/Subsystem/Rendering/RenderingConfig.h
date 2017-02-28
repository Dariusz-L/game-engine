#pragma once

#include <string>
#include <unordered_map>

enum class UniformType : unsigned char {
	NONE,

	PROJECTION,
	VIEW,
	MODEL,
	INVERSE_TRANSPOSE_MODEL,

	AMBIENT_STRENGTH,
	AMBIENT_COLOR,
	COLOR_DIFFUSE,
	COLOR_SPECULAR,
	SPECULAR_STRENGTH,

	LIGHT_POS,
	LIGHT_COLOR,
	VIEW_POS,

	TEX_DIFFUSE,
	TEX_SPECULAR,
	TEX_NORMAL,
};

static const std::unordered_map<std::string, UniformType> UNIFORM_NAMES {

	{ "projection",				UniformType::PROJECTION },
	{ "view",					UniformType::VIEW },
	{ "model",					UniformType::MODEL },
	{ "inverseTransposeModel",	UniformType::INVERSE_TRANSPOSE_MODEL },
	{ "ambientStrength",		UniformType::AMBIENT_STRENGTH },
	{ "ambientColor",			UniformType::AMBIENT_COLOR },
	{ "colorDiffuse",			UniformType::COLOR_DIFFUSE },
	{ "colorSpecular",			UniformType::COLOR_SPECULAR },
	{ "specularStrength",		UniformType::SPECULAR_STRENGTH },
	{ "lightPos",				UniformType::LIGHT_POS },
	{ "lightColor",				UniformType::LIGHT_COLOR },
	{ "viewPos",				UniformType::VIEW_POS },
	{ "texDiffuse",				UniformType::TEX_DIFFUSE },
	{ "texSpecular",			UniformType::TEX_SPECULAR },
	{ "texNormal",				UniformType::TEX_NORMAL }

};