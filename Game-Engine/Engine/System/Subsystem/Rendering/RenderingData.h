#pragma once

#include "RenderableObjects\RenderableObjects.h"
#include "Window.h"
#include <vector>

namespace Rendering {

	struct RenderingData {
		RenderableObjects renderable;
		std::vector<GameObject*> lights;

		GameObject* mainCamera;
		Window window;
	};

}