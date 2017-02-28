#pragma once

#include "System\Subsystem\Rendering\Asset\Mesh\Mesh.h"
#include "System\Resource\GameObject.h"
#include "System\Subsystem\Rendering\Asset\Shader.h"
#include "System\Subsystem\Rendering\Component\Material.h"

#include "System\EngineData.h"
#include "System\EngineSystem.h"
#include "System\Config\Platform.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class IManager;
class Window;

class Engine
{
private:
	static std::vector<IManager*> _managers;
	static bool _exitApp;

public:
	static EngineData data;
	static EngineSystem system;
	static void StartEngine();

	Engine();
	~Engine();

	void Init();
	void Loop();
	void Close();

	static void Exit();

	template<class T>
	static T* GetManager() {
		for (auto manager : _managers)
			if (dynamic_cast<T*>(manager) != nullptr)
				return static_cast<T*>(manager);

		return nullptr;
	}
};