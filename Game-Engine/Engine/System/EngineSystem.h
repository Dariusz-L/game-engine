#pragma once

#include "Subsystem\Subsystems.h"
#include "Resource\ResourceLoader.h"

struct EngineSystem {

	ResourceLoader	resourceLoader;
	Subsystems		subsystems;

};