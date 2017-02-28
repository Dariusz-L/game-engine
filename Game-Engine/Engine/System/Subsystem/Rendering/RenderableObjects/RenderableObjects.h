#pragma once

#include "ShaderBranch.h"

#include <vector>

class Shader;

namespace Rendering {
	struct RenderableObjects {
		std::vector<ShaderBranch> shaderBranch;
	};
}