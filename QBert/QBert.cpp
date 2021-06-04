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
	//load level from file
	
	//gamerules
	bool revertible;
	std::vector<std::string> colors{ "Pink", "Yellow"};
	//levelData
	int pyramidSize = 7;
	std::vector<int> plateRows{ 3 };
	//QBertData
	int qbertLives = 3;
	float jumpCooldownQBert = 0.5f;
	//SlickAndSamData
	float spawnIntervalSlick = 10.f;
	float jumpCooldownSlick = 1.f;
	//UggAndWrongwayData
	float spawnIntervalUgg = 10.f;
	float jumpCooldownUgg = 1.f;
	//CoilyData
	float spawnIntervalCoily = 10.f;
	float jumpCooldownCoily = 1.f;
	
	dae::LevelParser::LoadLevel(L"../Data/LevelData/Level1.json",
		revertible, colors,
		pyramidSize, plateRows,
		qbertLives, jumpCooldownQBert,
		spawnIntervalSlick, jumpCooldownSlick,
		spawnIntervalUgg, jumpCooldownUgg,
		spawnIntervalCoily, jumpCooldownCoily
	);
	
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

	//Level
	auto pyramid = std::make_shared<dae::GameObject>();
	dae::LevelComponent* pLevelComponent = nullptr;
	if (colors.size() == 2)
		pLevelComponent = new dae::LevelComponent(pyramidSize, colors[0], colors[1], revertible);
	else if(colors.size() == 3)
		pLevelComponent = new dae::LevelComponent(pyramidSize, colors[0], colors[2], colors[1], revertible);

	pyramid->AddComponent(pLevelComponent);
	scene.Add(pyramid);

	const float plateWidth = 20.f;

	for (size_t idx=0; idx< plateRows.size(); ++idx)
	{
		//Test Plate Left
		auto leftPlate = std::make_shared<dae::GameObject>();
		auto* pPlateLeftComp = new dae::PlateComponent(pLevelComponent, plateRows[idx], dae::Side::left);
		auto* pPlateLeftRenderComp = new dae::RenderComponent("Plate.png");
		leftPlate->AddComponent(pPlateLeftComp);
		leftPlate->AddComponent(pPlateLeftRenderComp);
		pPlateLeftRenderComp->SetDimensions(plateWidth, plateWidth);
		pPlateLeftComp->Initialize();
		scene.Add(leftPlate);

		//Test Plate Right
		auto rightPlate = std::make_shared<dae::GameObject>();
		auto* pPlateRightComp = new dae::PlateComponent(pLevelComponent, plateRows[idx], dae::Side::right);
		auto* pPlateRightRenderComp = new dae::RenderComponent("Plate.png");
		rightPlate->AddComponent(pPlateRightComp);
		rightPlate->AddComponent(pPlateRightRenderComp);
		pPlateRightRenderComp->SetDimensions(plateWidth, plateWidth);
		pPlateRightComp->Initialize();
		scene.Add(rightPlate);
	}
	
	//Enemies
	//Slick and Sam spawner
	auto pSAndSSpawner = std::make_shared<dae::GameObject>();
	auto* pSandSSpawnComponent = new dae::SlickAndSamSpawnerComponent(pLevelComponent, spawnIntervalSlick, jumpCooldownSlick);
	pSAndSSpawner->AddComponent(pSandSSpawnComponent);
	scene.Add(pSAndSSpawner);

	//Ugg + Wrong way spawner
	auto pUAndWSpawner = std::make_shared<dae::GameObject>();
	auto* pUandWSpawnComponent = new dae::UggAndWrongSpawnerComponent(pLevelComponent, spawnIntervalUgg, jumpCooldownUgg);
	pUAndWSpawner->AddComponent(pUandWSpawnComponent);
	scene.Add(pUAndWSpawner);

	//Coily spawner
	auto pCoilySpawner = std::make_shared<dae::GameObject>();
	auto* pCoilyspawnComponent = new dae::CoilySpawnerComponent(pLevelComponent, spawnIntervalCoily, jumpCooldownCoily);
	pCoilySpawner->AddComponent(pCoilyspawnComponent);
	scene.Add(pCoilySpawner);
	
	//Player
	auto pPlayerObserver = std::make_shared<dae::PlayerObserver>();
	
	auto QBert = std::make_shared<dae::GameObject>();
	auto* pQBertComponent = new dae::QBertComponent(pLevelComponent, jumpCooldownQBert);
	auto* pQBertRenderComponent = new dae::RenderComponent("Qbert.png");
	auto* pQBertLivesComponent = new dae::LivesComponent(qbertLives);
	auto* pQBertScoreComponent = new dae::ScoreComponent();
	auto* pQBertSubjectComponent = new dae::SubjectComponent();
	QBert->AddComponent(pQBertComponent);
	QBert->AddComponent(pQBertRenderComponent);
	QBert->AddComponent(pQBertLivesComponent);
	QBert->AddComponent(pQBertScoreComponent);
	QBert->AddComponent(pQBertSubjectComponent);
	pQBertComponent->ChangeCube(pLevelComponent->GetTopCube(), false, false, false);
	pQBertSubjectComponent->AddObserver(pPlayerObserver);
	scene.Add(QBert);

	//Player HUD
	const auto hudFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	
	//Title
	auto player1HUDTitle = std::make_shared<dae::GameObject>();
	std::string player1HUDTitleString = "Player 1";
	auto* pPlayer1HUDTitleText = new dae::TextComponent(player1HUDTitleString, hudFont);
	auto* pPlayer1HUDTitleRender = new dae::RenderComponent();
	player1HUDTitle->AddComponent(pPlayer1HUDTitleText);
	player1HUDTitle->AddComponent(pPlayer1HUDTitleRender);
	player1HUDTitle->SetPosition(10, 60);
	scene.Add(player1HUDTitle);

	//Lives remaining
	auto player1Lives = std::make_shared<dae::GameObject>();
	const std::string player1LivesString = "Remaining lives: " + std::to_string(pQBertLivesComponent->GetLivesRemaining());
	auto* pPlayer1LivesText = new dae::TextComponent(player1LivesString, hudFont);
	auto* pPlayer1LivesRender = new dae::RenderComponent();
	player1Lives->AddComponent(pPlayer1LivesText);
	player1Lives->AddComponent(pPlayer1LivesRender);
	player1Lives->SetPosition(10, 120);
	scene.Add(player1Lives);
	pPlayerObserver->SetLivesObject(player1Lives);

	//Score
	auto player1Score = std::make_shared<dae::GameObject>();
	const std::string player1ScoreString = "Score: " + std::to_string(pQBertScoreComponent->GetScore());
	auto* pPlayer1ScoreText = new dae::TextComponent(player1ScoreString, hudFont);
	auto* pPlayer1ScoreRender = new dae::RenderComponent();
	player1Score->AddComponent(pPlayer1ScoreText);
	player1Score->AddComponent(pPlayer1ScoreRender);
	player1Score->SetPosition(10, 150);
	scene.Add(player1Score);
	pPlayerObserver->SetScorebject(player1Score);
	
	//Adding input
	auto& input = dae::InputManager::GetInstance();

	const dae::ActionInfo GoNorthEast{ dae::ControllerButton::Up, SDL_SCANCODE_W, dae::InputState::Up };
	const dae::ActionInfo GoNorthWest{ dae::ControllerButton::Left, SDL_SCANCODE_A, dae::InputState::Up };
	const dae::ActionInfo GoSouthEast{ dae::ControllerButton::Right, SDL_SCANCODE_D, dae::InputState::Up };
	const dae::ActionInfo GoSouthWest{ dae::ControllerButton::Down, SDL_SCANCODE_S, dae::InputState::Up };

	//Player 1
	input.AddInput(0, GoNorthEast, new NorthEast(QBert));
	input.AddInput(0, GoNorthWest, new NorthWest(QBert));
	input.AddInput(0, GoSouthEast, new SouthEast(QBert));
	input.AddInput(0, GoSouthWest, new SouthWest(QBert));
}