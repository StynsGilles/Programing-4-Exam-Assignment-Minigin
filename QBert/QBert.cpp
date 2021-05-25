#include <MiniginPCH.h>
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
#include <string>
#include <FPSComponent.h>
#include <HealthComponent.h>
#include <InputManager.h>
#include <PlayerIndexComponent.h>
#include <PlayerObserver.h>
#include <ScoreComponent.h>
#include <SubjectComponent.h>
#include <TextComponent.h>
#include <ServiceLocator.h>
#include <SoundSystem.h>
#include <Scene.h>
#include "GameCommands.h"
#include "LevelComponent.h"

void LoadGame();
void InitPlayers(dae::Scene& scene);

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
	auto* pLevelComponent = new dae::LevelComponent("Yellow");
	pyramid->AddComponent(pLevelComponent);
	scene.Add(pyramid);
	
	//InitPlayers(scene);
}

void InitPlayers(dae::Scene&)
{
	//const auto hudFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	////Player 1
	//auto pPlayer1Observer = std::make_shared<dae::PlayerObserver>();

	//auto qBert = std::make_shared<dae::GameObject>();
	//auto* pQBertIndexComponent = new dae::PlayerIndexComponent(1);
	//auto* pQBertRenderComponent = new dae::RenderComponent();
	//auto* pQBertSubjectComponent = new dae::SubjectComponent();
	//auto* pQBertHealthComponent = new dae::HealthComponent();
	//auto* pQBertScoreComponent = new dae::ScoreComponent();
	//pQBertRenderComponent->SetTexture("Qbert.png");
	//pQBertRenderComponent->SetDimensions(50, 50);
	//pQBertSubjectComponent->AddObserver(pPlayer1Observer);
	//qBert->AddComponent(pQBertIndexComponent);
	//qBert->AddComponent(pQBertRenderComponent);
	//qBert->AddComponent(pQBertSubjectComponent);
	//qBert->AddComponent(pQBertHealthComponent);
	//qBert->AddComponent(pQBertScoreComponent);
	//qBert->SetPosition(50, 200);
	//scene.Add(qBert);

	////Player 1 HUD
	////Title
	//auto player1HUDTitle = std::make_shared<dae::GameObject>();
	//std::string player1HUDTitleString = "Player 1";
	//auto* pPlayer1HUDTitleText = new dae::TextComponent(player1HUDTitleString, hudFont);
	//auto* pPlayer1HUDTitleRender = new dae::RenderComponent();
	//player1HUDTitle->AddComponent(pPlayer1HUDTitleText);
	//player1HUDTitle->AddComponent(pPlayer1HUDTitleRender);
	//player1HUDTitle->SetPosition(10, 60);
	//scene.Add(player1HUDTitle);

	////Health
	//auto player1Health = std::make_shared<dae::GameObject>();
	//std::string player1HealthString = "Health: " + std::to_string(pQBertHealthComponent->GetHealth()) + "/" + std::to_string(pQBertHealthComponent->GetMaxHealth());
	//auto* pPlayer1HealthText = new dae::TextComponent(player1HealthString, hudFont);
	//auto* pPlayer1HealthRender = new dae::RenderComponent();
	//player1Health->AddComponent(pPlayer1HealthText);
	//player1Health->AddComponent(pPlayer1HealthRender);
	//player1Health->SetPosition(10, 90);
	//scene.Add(player1Health);
	//pPlayer1Observer->SetHealthObject(player1Health);

	////Lives remaining
	//auto player1Lives = std::make_shared<dae::GameObject>();
	//const std::string player1LivesString = "Remaining lives: " + std::to_string(pQBertHealthComponent->GetLivesRemaining());
	//auto* pPlayer1LivesText = new dae::TextComponent(player1LivesString, hudFont);
	//auto* pPlayer1LivesRender = new dae::RenderComponent();
	//player1Lives->AddComponent(pPlayer1LivesText);
	//player1Lives->AddComponent(pPlayer1LivesRender);
	//player1Lives->SetPosition(10, 120);
	//scene.Add(player1Lives);
	//pPlayer1Observer->SetLivesObject(player1Lives);

	////Score
	//auto player1Score = std::make_shared<dae::GameObject>();
	//const std::string player1ScoreString = "Score: " + std::to_string(pQBertScoreComponent->GetScore());
	//auto* pPlayer1ScoreText = new dae::TextComponent(player1ScoreString, hudFont);
	//auto* pPlayer1ScoreRender = new dae::RenderComponent();
	//player1Score->AddComponent(pPlayer1ScoreText);
	//player1Score->AddComponent(pPlayer1ScoreRender);
	//player1Score->SetPosition(10, 150);
	//scene.Add(player1Score);
	//pPlayer1Observer->SetScorebject(player1Score);

	////Player 2
	//auto pPlayer2Observer = std::make_shared<dae::PlayerObserver>();

	//auto evilQBert = std::make_shared<dae::GameObject>();
	//auto* pEvilQBertIndexComponent = new dae::PlayerIndexComponent(2);
	//auto* pEvilQBertRenderComponent = new dae::RenderComponent();
	//auto* pEvilQBertSubjectComponent = new dae::SubjectComponent();
	//auto* pEvilQBertHealthComponent = new dae::HealthComponent();
	//auto* pEvilQBertScoreComponent = new dae::ScoreComponent();
	//pEvilQBertRenderComponent->SetTexture("evilQbert.png");
	//pEvilQBertRenderComponent->SetDimensions(50, 50);
	//pEvilQBertSubjectComponent->AddObserver(pPlayer2Observer);
	//evilQBert->AddComponent(pEvilQBertIndexComponent);
	//evilQBert->AddComponent(pEvilQBertRenderComponent);
	//evilQBert->AddComponent(pEvilQBertSubjectComponent);
	//evilQBert->AddComponent(pEvilQBertHealthComponent);
	//evilQBert->AddComponent(pEvilQBertScoreComponent);
	//evilQBert->SetPosition(400, 200);
	//scene.Add(evilQBert);

	////Player 2 HUD
	////Title
	//auto player2HUDTitle = std::make_shared<dae::GameObject>();
	//std::string player2HUDTitleString = "Player 2";
	//auto* pPlayer2HUDTitleText = new dae::TextComponent(player2HUDTitleString, hudFont);
	//auto* pPlayer2HUDTitleRender = new dae::RenderComponent();
	//player2HUDTitle->AddComponent(pPlayer2HUDTitleText);
	//player2HUDTitle->AddComponent(pPlayer2HUDTitleRender);
	//player2HUDTitle->SetPosition(400, 60);
	//scene.Add(player2HUDTitle);

	////Health
	//auto player2Health = std::make_shared<dae::GameObject>();
	//std::string player2HealthString = "Health: " + std::to_string(pEvilQBertHealthComponent->GetHealth()) + "/" + std::to_string(pEvilQBertHealthComponent->GetMaxHealth());
	//auto* pPlayer2HealthText = new dae::TextComponent(player2HealthString, hudFont);
	//auto* pPlayer2HealthRender = new dae::RenderComponent();
	//player2Health->AddComponent(pPlayer2HealthText);
	//player2Health->AddComponent(pPlayer2HealthRender);
	//player2Health->SetPosition(400, 90);
	//scene.Add(player2Health);
	//pPlayer2Observer->SetHealthObject(player2Health);

	////Lives remaining
	//auto player2Lives = std::make_shared<dae::GameObject>();
	//const std::string player2LivesString = "Remaining lives: " + std::to_string(pEvilQBertHealthComponent->GetLivesRemaining());
	//auto* pPlayer2LivesText = new dae::TextComponent(player2LivesString, hudFont);
	//auto* pPlayer2LivesRender = new dae::RenderComponent();
	//player2Lives->AddComponent(pPlayer2LivesText);
	//player2Lives->AddComponent(pPlayer2LivesRender);
	//player2Lives->SetPosition(400, 120);
	//scene.Add(player2Lives);
	//pPlayer2Observer->SetLivesObject(player2Lives);

	////Score
	//auto player2Score = std::make_shared<dae::GameObject>();
	//const std::string player2ScoreString = "Score: " + std::to_string(pEvilQBertScoreComponent->GetScore());
	//auto* pPlayer2ScoreText = new dae::TextComponent(player2ScoreString, hudFont);
	//auto* pPlayer2ScoreRender = new dae::RenderComponent();
	//player2Score->AddComponent(pPlayer2ScoreText);
	//player2Score->AddComponent(pPlayer2ScoreRender);
	//player2Score->SetPosition(400, 150);
	//scene.Add(player2Score);
	//pPlayer2Observer->SetScorebject(player2Score);

	////Adding input
	//auto& input = dae::InputManager::GetInstance();

	//const dae::ActionInfo killQbertAction{ dae::ControllerButton::ButtonA, SDL_SCANCODE_1, dae::InputState::Up };
	//const dae::ActionInfo damageQbertAction{ dae::ControllerButton::ButtonB, SDL_SCANCODE_2, dae::InputState::Up };
	//const dae::ActionInfo awardScoreAction{ dae::ControllerButton::ButtonX, SDL_SCANCODE_3, dae::InputState::Up };

	////Player 1
	//input.AddInput(0, killQbertAction, new Kill(qBert));
	//input.AddInput(0, damageQbertAction, new Damage(qBert));
	//input.AddInput(0, awardScoreAction, new Score(qBert));

	////Player 2
	//input.AddInput(1, killQbertAction, new Kill(evilQBert));
	//input.AddInput(1, damageQbertAction, new Damage(evilQBert));
	//input.AddInput(1, awardScoreAction, new Score(evilQBert));
}