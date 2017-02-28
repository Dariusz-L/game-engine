#pragma once

#include "MG.h"

#include <vector>

class Material;

namespace Rendering {
	struct MaterialBranch {
		Material* material;
		std::vector<MG> mg;
	};
}