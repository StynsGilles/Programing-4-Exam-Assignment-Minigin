#include "pch.h"
#include "VersusScene.h"
#include "CoilySpawnerComponent.h"
#include "EnemyPositionComponent.h"
#include "FPSComponent.h"
#include "GameCommands.h"
#include "LevelComponent.h"
#include "LevelParser.h"
#include "LivesComponent.h"
#include "PlateComponent.h"
#include "PlayerObserver.h"
#include "QBertComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"
#include "SlickAndSamSpawnerComponent.h"
#include "SubjectComponent.h"
#include "TextComponent.h"
#include "UggAndWrongSpawnerComponent.h"

dae::VersusScene::VersusScene(const std::string& name, const std::wstring& fileName)
	: BaseLevelScene(name, fileName)
{
}

void dae::VersusScene::Initialize()
{
	Scene::Initialize();

	//load level from file

	//gamerules
	bool revertible;
	std::vector<std::string> colors{ "Pink", "Yellow" };
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

	dae::LevelParser::LoadLevel(L"../Data/LevelData/" + m_FileName,
		revertible, colors,
		pyramidSize, plateRows,
		qbertLives, jumpCooldownQBert,
		spawnIntervalSlick, jumpCooldownSlick,
		spawnIntervalUgg, jumpCooldownUgg,
		spawnIntervalCoily, jumpCooldownCoily
	);

	//Create objects
	

	const auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fps = std::make_shared<GameObject>();
	auto* pFPSTextureComponent = new RenderComponent();
	auto* pTextComponent = new TextComponent("00 fps", fpsFont);
	auto* pFPSComponent = new FPSComponent(pTextComponent);
	pTextComponent->SetColor(SDL_Color{ 255, 255, 0 });
	fps->AddComponent(pFPSTextureComponent);
	fps->AddComponent(pTextComponent);
	fps->AddComponent(pFPSComponent);
	Add(fps);

	//Level
	auto pyramid = std::make_shared<GameObject>();
	LevelComponent* pLevelComponent = nullptr;
	if (colors.size() == 2)
		pLevelComponent = new LevelComponent(pyramidSize, colors[0], colors[1], revertible);
	else if (colors.size() == 3)
		pLevelComponent = new LevelComponent(pyramidSize, colors[0], colors[2], colors[1], revertible);

	pyramid->AddComponent(pLevelComponent);
	Add(pyramid);

	const float plateWidth = 20.f;

	for (size_t idx = 0; idx < plateRows.size(); ++idx)
	{
		//Test Plate Left
		auto leftPlate = std::make_shared<GameObject>();
		auto* pPlateLeftComp = new PlateComponent(pLevelComponent, plateRows[idx], Side::left);
		auto* pPlateLeftRenderComp = new RenderComponent("Plate.png");
		leftPlate->AddComponent(pPlateLeftComp);
		leftPlate->AddComponent(pPlateLeftRenderComp);
		pPlateLeftRenderComp->SetDimensions(plateWidth, plateWidth);
		pPlateLeftComp->Initialize();
		Add(leftPlate);

		//Test Plate Right
		auto rightPlate = std::make_shared<GameObject>();
		auto* pPlateRightComp = new PlateComponent(pLevelComponent, plateRows[idx], Side::right);
		auto* pPlateRightRenderComp = new RenderComponent("Plate.png");
		rightPlate->AddComponent(pPlateRightComp);
		rightPlate->AddComponent(pPlateRightRenderComp);
		pPlateRightRenderComp->SetDimensions(plateWidth, plateWidth);
		pPlateRightComp->Initialize();
		Add(rightPlate);
	}

	//Enemies
	//Slick and Sam spawner
	auto pSAndSSpawner = std::make_shared<GameObject>();
	auto* pSandSSpawnComponent = new SlickAndSamSpawnerComponent(pLevelComponent, spawnIntervalSlick, jumpCooldownSlick);
	pSAndSSpawner->AddComponent(pSandSSpawnComponent);
	Add(pSAndSSpawner);

	//Ugg + Wrong way spawner
	auto pUAndWSpawner = std::make_shared<GameObject>();
	auto* pUandWSpawnComponent = new UggAndWrongSpawnerComponent(pLevelComponent, spawnIntervalUgg, jumpCooldownUgg);
	pUAndWSpawner->AddComponent(pUandWSpawnComponent);
	Add(pUAndWSpawner);

	//Coily spawner
	auto pCoilySpawner = std::make_shared<GameObject>();
	auto* pCoilyspawnComponent = new CoilySpawnerComponent(pLevelComponent, spawnIntervalCoily, jumpCooldownCoily, true);
	pCoilySpawner->AddComponent(pCoilyspawnComponent);
	Add(pCoilySpawner);
	
	//Player
	auto pPlayerObserver = std::make_shared<PlayerObserver>();

	auto QBert = std::make_shared<GameObject>();
	auto* pQBertComponent = new QBertComponent(pLevelComponent, jumpCooldownQBert);
	auto* pQBertRenderComponent = new RenderComponent("Qbert.png");
	auto* pQBertLivesComponent = new LivesComponent(qbertLives);
	auto* pQBertScoreComponent = new ScoreComponent();
	auto* pQBertSubjectComponent = new SubjectComponent();
	QBert->AddComponent(pQBertComponent);
	QBert->AddComponent(pQBertRenderComponent);
	QBert->AddComponent(pQBertLivesComponent);
	QBert->AddComponent(pQBertScoreComponent);
	QBert->AddComponent(pQBertSubjectComponent);
	pQBertComponent->ChangeCube(pLevelComponent->GetTopCube(), false, false, false);
	pQBertSubjectComponent->AddObserver(pPlayerObserver);
	Add(QBert);

	//Player HUD
	const auto hudFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//Title
	auto player1HUDTitle = std::make_shared<GameObject>();
	std::string player1HUDTitleString = "Player 1";
	auto* pPlayer1HUDTitleText = new TextComponent(player1HUDTitleString, hudFont);
	auto* pPlayer1HUDTitleRender = new RenderComponent();
	player1HUDTitle->AddComponent(pPlayer1HUDTitleText);
	player1HUDTitle->AddComponent(pPlayer1HUDTitleRender);
	player1HUDTitle->SetPosition(10, 60);
	Add(player1HUDTitle);

	//Lives remaining
	auto player1Lives = std::make_shared<GameObject>();
	const std::string player1LivesString = "Remaining lives: " + std::to_string(pQBertLivesComponent->GetLivesRemaining());
	auto* pPlayer1LivesText = new TextComponent(player1LivesString, hudFont);
	auto* pPlayer1LivesRender = new RenderComponent();
	player1Lives->AddComponent(pPlayer1LivesText);
	player1Lives->AddComponent(pPlayer1LivesRender);
	player1Lives->SetPosition(10, 120);
	Add(player1Lives);
	pPlayerObserver->SetLivesObject(player1Lives);

	//Score
	auto player1Score = std::make_shared<GameObject>();
	const std::string player1ScoreString = "Score: " + std::to_string(pQBertScoreComponent->GetScore());
	auto* pPlayer1ScoreText = new TextComponent(player1ScoreString, hudFont);
	auto* pPlayer1ScoreRender = new RenderComponent();
	player1Score->AddComponent(pPlayer1ScoreText);
	player1Score->AddComponent(pPlayer1ScoreRender);
	player1Score->SetPosition(10, 150);
	Add(player1Score);
	pPlayerObserver->SetScorebject(player1Score);

	//Adding input
	const ActionInfo GoNorthEast{ ControllerButton::Up, SDL_SCANCODE_W, InputState::Up };
	const ActionInfo GoNorthWest{ ControllerButton::Left, SDL_SCANCODE_A, InputState::Up };
	const ActionInfo GoSouthEast{ ControllerButton::Right, SDL_SCANCODE_D, InputState::Up };
	const ActionInfo GoSouthWest{ ControllerButton::Down, SDL_SCANCODE_S, InputState::Up };

	const ActionInfo CoilyNorthEast{ ControllerButton::Up, SDL_SCANCODE_UP, InputState::Up };
	const ActionInfo CoilyNorthWest{ ControllerButton::Left, SDL_SCANCODE_LEFT, InputState::Up };
	const ActionInfo CoilySouthEast{ ControllerButton::Right, SDL_SCANCODE_RIGHT, InputState::Up };
	const ActionInfo CoilySouthWest{ ControllerButton::Down, SDL_SCANCODE_DOWN, InputState::Up };
	
	//Player 1
	m_InputManager->AddInput(0, GoNorthEast, new NorthEast(QBert));
	m_InputManager->AddInput(0, GoNorthWest, new NorthWest(QBert));
	m_InputManager->AddInput(0, GoSouthEast, new SouthEast(QBert));
	m_InputManager->AddInput(0, GoSouthWest, new SouthWest(QBert));

	//Coily
	m_InputManager->AddInput(1, CoilyNorthEast, new NorthEastCoily(std::weak_ptr<GameObject>()));
	m_InputManager->AddInput(1, CoilyNorthWest, new NorthWestCoily(std::weak_ptr<GameObject>()));
	m_InputManager->AddInput(1, CoilySouthEast, new SouthEastCoily(std::weak_ptr<GameObject>()));
	m_InputManager->AddInput(1, CoilySouthWest, new SouthWestCoily(std::weak_ptr<GameObject>()));
}