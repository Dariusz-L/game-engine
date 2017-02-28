#pragma once
#include "..\Core\IManager.h"

#include "ResourceInfo.h"
#include "..\System\Resource\Asset\Asset.h"
#include "..\System\Subsystem\Rendering\Asset\Mesh\ObjModel.h"
#include "..\System\Subsystem\Rendering\Asset\Mesh\Mesh.h"
#include "..\System\Subsystem\Rendering\Asset\Texture.h"
#include "..\System\Subsystem\Rendering\Asset\MtlMaterial.h"
#include "..\System\Subsystem\Rendering\Asset\Shader.h"

#include "..\System\Utility\Containers\Pool.h"
#include "..\System\Subsystem\Rendering\Component\Model.h"
#include "..\System\Subsystem\Rendering\Component\Light.h"
#include "..\System\Subsystem\Rendering\Component\Material.h"
#include "..\System\Subsystem\Rendering\Component\Camera.h"

#include "..\System\Resource\GameObject.h"

#include "..\System\Utility\String\StringUtility.h"
#include "..\Utils\ParseUtil.h"
#include "..\Loader\FileLoader.h"
#include "..\Engine.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <set>

using namespace std;

class ResourceManager :
	public IManager
{
public:
	ResourceManager();
	~ResourceManager();

	void Init() override;
	void Run() override {}
	void Close() override;

	Assets* GetResources();
	std::vector<GameObject*>* GetGameObjects();
	Components* GetComponents();

	template<class T>
	T* GetResourceByID(int id) {
		SpecificAssets* resourceBank = Engine::data.resources.assets[typeid(T)];

		if (id == -1)
			return nullptr;

		try {
			return static_cast<T*>((*resourceBank).at(id));
		} catch (std::out_of_range e) {
			return nullptr;
		}
	}

	template<class T>
	T* GetResourceByName(const std::string& name) {
		SpecificAssets* resourceBank = Engine::data.resources.assets[typeid(T)];
		for (auto r : *resourceBank) {
			if (r.second->GetName() == name) {
				return static_cast<T*>(r.second);
			}
		}
		return nullptr;
	}

	template<class T>
	T* GetComponentByID(int id) {
		ComponentPool* pool = Engine::data.resources.components[typeid(T)];

		if (id == -1)
			return nullptr;

		return static_cast<T*>(pool->GetObjectOfID(id));
	}

	Component* GetComponentByID(const std::string& typeName, int id);

	GameObject* GetGameObjectByID(int id) {
		return Engine::data.resources.gameObjects.GetObjectOfID(id);
	}

	template<class T>
	void InitResources(const string& cfgName, int filesOffset = 1)  {
		using namespace Rendering;

		unordered_map<int, Asset*>* resourceBank = new unordered_map<int, Asset*>();
		vector<string> splitted = Utility::String::Split(cfgName, '.');
		string directory = "data/" + splitted[0] + '/';
		ResourceInfo resourceBankInfo(resourceBank, directory, FileLoader::LoadCfgFile(directory + cfgName));

		std::vector<std::string>& filesPaths = resourceBankInfo.filesPaths;
		for (int i = 0; i < filesPaths.size(); i += filesOffset) {
			T* resource = new T();

			vector<string> filePathsGroup;
			for (int j = 0; j < filesOffset; j++)
				filePathsGroup.push_back(Utility::String::Concat(directory, filesPaths[i + j]));

			resource->SetID((i / filesOffset));
			resource->Load(filePathsGroup);

			resourceBank->emplace((i / filesOffset), resource);
		}

		Engine::data.resources.assets.emplace(typeid(T), resourceBank);
	}

	template<class T>
	void InitComponent(const string& data) {
		Components* components = &Engine::data.resources.components;
		auto it = components->find(typeid(T));
		if (it == components->end()) {
			Pool<Component>* pool = new Pool<Component>();
			pool->Init<T>(1000);
			components->emplace(typeid(T), pool);

			std::string typeName = Utility::String::RemoveSubstring(typeid(T).name(), "class ");
			Engine::data.resources.resourceTypesMap.emplace(typeName, typeid(T));
		}

		auto parsedData = ParseUtil::ParseLoadedData(data);
		if (stoi(parsedData["isFromFile"]) == 0) {
			T* component = static_cast<T*>(components->operator[](typeid(T))->GetNext());
			component->Parse(parsedData);
		}
	}

	template<class T>
	T* InitComponent(ParsedData& parsedData) {
		Components* components = &Engine::data.resources.components;
		auto it = components->find(typeid(T));
		if (it == components->end()) {
			Pool<Component>* pool = new Pool<Component>();
			pool->Init<T>(150);
			components->emplace(typeid(T), pool);

			std::string typeName = Utility::String::RemoveSubstring(typeid(T).name(), "class ");
			Engine::data.resources.resourceTypesMap.emplace(typeName, typeid(T));
		}

		auto pool = components->operator[](typeid(T));
		T* component = static_cast<T*>(pool->GetNext());
		component->Parse(parsedData);

		return component;
	}

	void InitGameObject(const string& data) {
		auto parsedData = ParseUtil::ParseLoadedData(data);

		GameObject* gameObject = Engine::data.resources.gameObjects.GetNext();
		gameObject->SetName(parsedData["name"]);
		gameObject->Parse(parsedData);
	}
};