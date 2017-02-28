#pragma once

#include "Asset\Asset.h"
#include "Asset\SpecificAssets.h"
#include "Asset\Assets.h"

#include "Component\Component.h"
#include "Component\Components.h"

#include <unordered_map>
#include <typeindex>

using GameObjects = Pool<GameObject>;

struct ResourceData {

	std::unordered_map<std::string, std::type_index> resourceTypesMap;

	Assets				assets;
	Components			components;
	GameObjects			gameObjects;

};