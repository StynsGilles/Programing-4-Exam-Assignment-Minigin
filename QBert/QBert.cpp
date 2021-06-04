#include "pch.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include <memory>
#include <Minigin.h>
#include <GameObject.h>
#include <SceneManager.h>
#include <RenderComponent.h>
#include <ResourceManager.h>
#include <FPSComponent.h>
#include <InputManager.h>
#include <SubjectComponent.h>
#include <TextComponent.h>
#include <ServiceLocator.h>
#include <SoundSystem.h>
#include <Scene.h>
#include "SlickAndSamSpawnerComponent.h"
#include "GameCommands.h"
#include "LevelComponent.h"
#include "LivesComponent.h"
#include "PlayerObserver.h"
#include "QBertComponent.h"
#include "UggAndWrongSpawnerComponent.h"
#include "CoilySpawnerComponent.h"
#include "PlateComponent.h"
#include "LevelParser.h"
#include "LevelScene.h"

void LoadGame();

int main(int, char* [])
{
	dae::Minigin engine;
	engine.Initialize();
	LoadGame();
	engine.Run();
	return 0;
}

/**
 * Code constructing the scene world starts here
 */
void LoadGame()
{
	
	// tell the resource manager where he can find the game data
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SoundSystem>());
	const auto levelScene = std::shared_ptr<dae::LevelScene>(new dae::LevelScene("Level1"));
	dae::SceneManager::GetInstance().AddScene(levelScene);

	levelScene->Initialize();
}