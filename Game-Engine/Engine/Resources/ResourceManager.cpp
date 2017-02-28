#include "ResourceManager.h"

#include "..\Engine.h"

#include <iostream>

using namespace std;
using namespace Utility::String;

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager()
{
	Assets*		assets		= &Engine::data.resources.assets;
	Components*	components	= &Engine::data.resources.components;

	for (auto r : *assets) {
		for (auto b : *r.second)
			delete b.second;
		delete r.second;
	}
	assets->clear();

	for (auto p : *components) {
		delete p.second;
	}
	components->clear();
}

void ResourceManager::Init()
{
	Engine::data.resources.gameObjects.Init<GameObject>(1000);

	FileLoader::ParseFileByLine("data/data.cfg", 
		[this]
		(std::string line) -> bool {

		line = RemoveSubstring(line, "\r");
		if (IfContainStr(line, "//")) return true;
		vector<string> data = Utility::String::Split(line, '=');
		if (data.size() == 0) return true;

		// COMPONENTS
		else if (IfContainStr(data[0], "CModel"))			InitComponent<Model>(data[1]);
		else if (IfContainStr(data[0], "CCamera"))			InitComponent<Camera>(data[1]);
		else if (IfContainStr(data[0], "CLight"))			InitComponent<Light>(data[1]);
		else if (IfContainStr(data[0], "CMaterial")) 		InitComponent<Material>(data[1]);

		// GAME OBJECTS
		else if (IfContainStr(data[0], "GGameObject"))		
			InitGameObject(data[1]);

		return true;
	});
	SDL_Log("Resource");

}

void ResourceManager::Close()
{
}

Assets* ResourceManager::GetResources()
{
	return &Engine::data.resources.assets;
}

std::vector<GameObject*>* ResourceManager::GetGameObjects()
{
	return Engine::data.resources.gameObjects.GetActiveObjects();
}

Components* ResourceManager::GetComponents()
{
	return &Engine::data.resources.components;
}

Component* ResourceManager::GetComponentByID(const std::string& typeName, int id) {
	auto i = Engine::data.resources.resourceTypesMap.at(typeName);
	Pool<Component>* pool = Engine::data.resources.components[i];
	if (id == -1 || pool == nullptr)
		return nullptr;

	return pool->GetObjectOfID(id);
}