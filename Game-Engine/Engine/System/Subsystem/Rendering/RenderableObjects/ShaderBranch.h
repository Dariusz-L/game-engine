#pragma once

#include "MaterialBranch.h"

#include <vector>

class Shader;

namespace Rendering {
	struct ShaderBranch {
		Shader* shader;
		std::vector<MaterialBranch> materialBranch;
	};
}