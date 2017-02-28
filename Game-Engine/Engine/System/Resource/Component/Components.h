#pragma once

#include "ComponentPool.h"

#include <unordered_map>
#include <typeindex>

using Components = std::unordered_map<std::type_index, ComponentPool*>;