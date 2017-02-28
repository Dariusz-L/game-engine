#pragma once

#include "ISubsystem.h"

#include "Rendering\RenderingSystem.h"

#include <vector>

struct Subsystems {

	std::vector<ISubsystem*> all;

	Rendering::RenderingSystem rendering;
};