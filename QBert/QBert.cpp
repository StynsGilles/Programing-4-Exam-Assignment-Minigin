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
#include "SinglePlayerScene.h"

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
	auto& sceneManager = dae::SceneManager::GetInstance();
	
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SoundSystem>());
	const auto level1Scene = std::make_shared<dae::SinglePlayerScene>("Level1", L"Level1.json");
	sceneManager.AddScene(level1Scene);
	level1Scene->Initialize();

	const auto level2Scene = std::make_shared<dae::SinglePlayerScene>("Level2", L"Level2.json");
	sceneManager.AddScene(level2Scene);
	level2Scene->Initialize();

	const auto level3Scene = std::make_shared<dae::SinglePlayerScene>("Level2", L"Level2.json");
	sceneManager.AddScene(level3Scene);
	level3Scene->Initialize();

	sceneManager.SetActiveScene("Level1");
}