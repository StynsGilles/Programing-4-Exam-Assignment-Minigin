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
#include "HealthComponent.h"
#include <InputManager.h>
#include "PlayerIndexComponent.h"
#include "PlayerObserver.h"
#include "ScoreComponent.h"
#include <SubjectComponent.h>
#include <TextComponent.h>
#include <ServiceLocator.h>
#include <SoundSystem.h>
#include <Scene.h>
#include "GameCommands.h"
#include "LevelComponent.h"
#include "QBertComponent.h"

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
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Create objects
	auto go = std::make_shared<dae::GameObject>();
	auto* pBackgroundTextureComponent = new dae::RenderComponent();
	pBackgroundTextureComponent->SetTexture("background.jpg");
	go->AddComponent(pBackgroundTextureComponent);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto* pLogoTextureComponent = new dae::RenderComponent();
	pLogoTextureComponent->SetTexture("logo.png");
	go->AddComponent(pLogoTextureComponent);
	go->SetPosition(216, 180);
	scene.Add(go);

	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::GameObject>();
	auto* pTextTextureComponent = new dae::RenderComponent();
	dae::TextComponent* pTextInfoComponent = new dae::TextComponent("Programming 4 Assignment", font);
	to->AddComponent(pTextTextureComponent);
	to->AddComponent(pTextInfoComponent);
	to->SetPosition(80, 20);
	scene.Add(to);

	const auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fps = std::make_shared<dae::GameObject>();
	auto* pFPSTextureComponent = new dae::RenderComponent();
	dae::TextComponent* pTextComponent = new dae::TextComponent("00 fps", fpsFont);
	auto* pFPSComponent = new dae::FPSComponent(pTextComponent);
	pTextComponent->SetColor(SDL_Color{ 255, 255, 0 });
	fps->AddComponent(pFPSTextureComponent);
	fps->AddComponent(pTextComponent);
	fps->AddComponent(pFPSComponent);
	scene.Add(fps);

	auto pyramid = std::make_shared<dae::GameObject>();
	auto* pLevelComponent = new dae::LevelComponent("Pink", "Yellow", true);
	pyramid->AddComponent(pLevelComponent);
	scene.Add(pyramid);

	auto QBert = std::make_shared<dae::GameObject>();
	auto* pQBertComponent = new dae::QBertComponent();
	auto* pQBertRenderComponent = new dae::RenderComponent("Qbert.png");
	QBert->AddComponent(pQBertComponent);
	QBert->AddComponent(pQBertRenderComponent);
	pQBertComponent->ChangeCube(pLevelComponent->GetTopCube());
	scene.Add(QBert);

	//Adding input
	auto& input = dae::InputManager::GetInstance();

	const dae::ActionInfo GoNorthEast{ dae::ControllerButton::Up, SDL_SCANCODE_W, dae::InputState::Up };
	const dae::ActionInfo GoNorthWest{ dae::ControllerButton::Left, SDL_SCANCODE_A, dae::InputState::Up };
	const dae::ActionInfo GoSouthEast{ dae::ControllerButton::Right, SDL_SCANCODE_D, dae::InputState::Up };
	const dae::ActionInfo GoSouthWest{ dae::ControllerButton::Down, SDL_SCANCODE_S, dae::InputState::Up };

	//Player 1
	input.AddInput(0, GoNorthEast, new NorthEast(QBert, pyramid));
	input.AddInput(0, GoNorthWest, new NorthWest(QBert, pyramid));
	input.AddInput(0, GoSouthEast, new SouthEast(QBert, pyramid));
	input.AddInput(0, GoSouthWest, new SouthWest(QBert, pyramid));
}