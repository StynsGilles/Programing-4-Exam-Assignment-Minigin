#include "pch.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include <memory>
#include <Minigin.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include <TextComponent.h>
#include <ServiceLocator.h>
#include <SoundSystem.h>
#include "LevelParser.h"
#include "SinglePlayerScene.h"
#include "VersusScene.h"
#include "CoopScene.h"

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

	//const auto versusScene = std::make_shared<dae::VersusScene>("VersusLevel", L"Level1.json");
	//sceneManager.AddScene(versusScene);
	//versusScene->Initialize();
	
	//const auto level1Scene = std::make_shared<dae::SinglePlayerScene>("Level1", L"Level1.json");
	//sceneManager.AddScene(level1Scene);
	//level1Scene->Initialize();

	//const auto level2Scene = std::make_shared<dae::SinglePlayerScene>("Level2", L"Level2.json");
	//sceneManager.AddScene(level2Scene);
	//level2Scene->Initialize();

	//const auto level3Scene = std::make_shared<dae::SinglePlayerScene>("Level2", L"Level2.json");
	//sceneManager.AddScene(level3Scene);
	//level3Scene->Initialize();

	const auto coopScene = std::make_shared<dae::CoopScene>("CoopLevel", L"Level1.json");
	sceneManager.AddScene(coopScene);
	coopScene->Initialize();
	
	sceneManager.SetActiveScene("CoopLevel");
}