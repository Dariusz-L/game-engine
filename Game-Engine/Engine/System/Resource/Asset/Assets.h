#pragma once

#include "SpecificAssets.h"

#include <unordered_map>
#include <typeindex>

using Assets = std::unordered_map<std::type_index, SpecificAssets*>;