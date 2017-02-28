#include "Engine.h"
#include "System\Config\Include\IncludeSDL.h"

#include "Events\EventManager.h"
#include "Resources\ResourceManager.h"

#include "Core\IManager.h"

#include "Time\TimeManager.h"
#include "Input\StandardInputController.h"

#include "System\Resource\Asset\Parser\Image\ImageAssetParser.h"
#include "System\Resource\ResourceLoader.h"

std::vector<IManager*> Engine::_managers;
EngineData Engine::data;
EngineSystem Engine::system;
bool Engine::_exitApp = false;

#ifdef _MSC_VER
	#undef main
#endif

#ifndef staticlibrary
int main(int argc, char** argv) {
	Engine::StartEngine();
	return 0;
}
#endif

void Engine::StartEngine()
{
	Engine *app = new Engine;
	app->Init();
	app->Loop();
	app->Close();
	delete app;
}

Engine::Engine()
{
	_managers.push_back(new EventManager());
	_managers.push_back(new ResourceManager());

	system.subsystems.all.push_back(&system.subsystems.rendering);
}

Engine::~Engine()
{
	for (auto manager : _managers)
		delete manager;

	_managers.clear();
}

#include "System\Config\Include\IncludeAssimp.h"

void Engine::Init()
{
	system.resourceLoader.ParseAllAssets();
	//system.resourceLoader.UnparseAllAssets();
	for (auto subsystem : system.subsystems.all)
		subsystem->OnStart();

	for (auto manager : _managers)
		manager->Init();

#ifndef staticlibrary
	Engine::GetManager<EventManager>()->AddHandler(new StandardInputController());
#endif
}

void Engine::Loop() {

	while (!_exitApp) {
		Timer::ProcessTimer();
		for (auto m : _managers)
			m->Run();

		for (auto subsystem : system.subsystems.all)
			subsystem->Update();
	}

}

void Engine::Close() {
	std::reverse(_managers.begin(), _managers.end());

	for (auto manager : _managers)
		manager->Close();

	std::reverse(_managers.begin(), _managers.end());

	for (auto subsystem : system.subsystems.all)
		subsystem->OnEnd();

	SDL_Quit();
}

void Engine::Exit() {
	_exitApp = true;
}