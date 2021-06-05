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
#include "MainMenuScene.h"

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

	const auto mainMenuScene = std::make_shared<dae::MainMenuScene>("MainMenu");
	sceneManager.AddScene(mainMenuScene);
	mainMenuScene->Initialize();
	
	const auto level1Scene = std::make_shared<dae::SinglePlayerScene>("Level1", L"Level1.json");
	sceneManager.AddScene(level1Scene);
	level1Scene->Initialize();

	const auto level2Scene = std::make_shared<dae::SinglePlayerScene>("Level2", L"Level2.json");
	sceneManager.AddScene(level2Scene);
	level2Scene->Initialize();

	const auto level3Scene = std::make_shared<dae::SinglePlayerScene>("Level3", L"Level3.json");
	sceneManager.AddScene(level3Scene);
	level3Scene->Initialize();

	const auto versusLv1Scene = std::make_shared<dae::VersusScene>("VersusLevel1", L"Level1.json");
	sceneManager.AddScene(versusLv1Scene);
	versusLv1Scene->Initialize();

	const auto versusLv2Scene = std::make_shared<dae::VersusScene>("VersusLevel2", L"Level2.json");
	sceneManager.AddScene(versusLv2Scene);
	versusLv2Scene->Initialize();

	const auto versusLv3Scene = std::make_shared<dae::VersusScene>("VersusLevel3", L"Level3.json");
	sceneManager.AddScene(versusLv3Scene);
	versusLv3Scene->Initialize();
	
	const auto coopLv1Scene = std::make_shared<dae::CoopScene>("CoopLevel1", L"Level1.json");
	sceneManager.AddScene(coopLv1Scene);
	coopLv1Scene->Initialize();

	const auto coopLv2Scene = std::make_shared<dae::CoopScene>("CoopLevel2", L"Level2.json");
	sceneManager.AddScene(coopLv2Scene);
	coopLv2Scene->Initialize();


	const auto coopLv3Scene = std::make_shared<dae::CoopScene>("CoopLevel3", L"Level3.json");
	sceneManager.AddScene(coopLv3Scene);
	coopLv3Scene->Initialize();
	
	sceneManager.SetActiveScene("MainMenu");
}