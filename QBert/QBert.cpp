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

	const auto level1Scene = std::make_shared<dae::SinglePlayerScene>("Level1", 1);
	sceneManager.AddScene(level1Scene);

	const auto level2Scene = std::make_shared<dae::SinglePlayerScene>("Level2", 2);
	sceneManager.AddScene(level2Scene);

	const auto level3Scene = std::make_shared<dae::SinglePlayerScene>("Level3", 3);
	sceneManager.AddScene(level3Scene);

	const auto versusLv1Scene = std::make_shared<dae::VersusScene>("VersusLevel1", 1);
	sceneManager.AddScene(versusLv1Scene);

	const auto versusLv2Scene = std::make_shared<dae::VersusScene>("VersusLevel2", 2);
	sceneManager.AddScene(versusLv2Scene);

	const auto versusLv3Scene = std::make_shared<dae::VersusScene>("VersusLevel3", 3);
	sceneManager.AddScene(versusLv3Scene);

	const auto coopLv1Scene = std::make_shared<dae::CoopScene>("CoopLevel1", 1);
	sceneManager.AddScene(coopLv1Scene);

	const auto coopLv2Scene = std::make_shared<dae::CoopScene>("CoopLevel2", 2);
	sceneManager.AddScene(coopLv2Scene);

	const auto coopLv3Scene = std::make_shared<dae::CoopScene>("CoopLevel3", 3);
	sceneManager.AddScene(coopLv3Scene);

	sceneManager.SetActiveScene("MainMenu");
}