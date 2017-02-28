#pragma once

#include "Resource\ResourceData.h"
#include "Subsystem\Rendering\RenderingData.h"

struct EngineData {
	Rendering::RenderingData	rendering;
	ResourceData resources;
};