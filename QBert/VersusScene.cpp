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

dae::VersusScene::VersusScene(const std::string& name, int level)
	: BaseLevelScene(name, level)
{
}

void dae::VersusScene::Initialize()
{
	BaseLevelScene::Initialize();

	//load level from file

	//gamerules
	bool revertible;
	std::vector<std::string> colors{ "Pink", "Yellow" };
	//levelData
	int pyramidSize = 7;
	float cubeWidth = 64.f;
	float cubeHeight = 64.f;
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

	LevelParser::LoadLevel(L"../Data/LevelData/Level" + std::to_wstring(m_Level) + L".json",
		revertible, colors,
		pyramidSize, cubeWidth,
		cubeHeight, plateRows,
		qbertLives, jumpCooldownQBert,
		spawnIntervalSlick, jumpCooldownSlick,
		spawnIntervalUgg, jumpCooldownUgg,
		spawnIntervalCoily, jumpCooldownCoily
	);

	//Level
	auto pyramid = std::make_shared<GameObject>();
	LevelComponent* pLevelComponent = nullptr;
	if (colors.size() == 2)
		pLevelComponent = new LevelComponent(pyramidSize, cubeWidth, cubeHeight, colors[0], colors[1], revertible);
	else if (colors.size() == 3)
		pLevelComponent = new LevelComponent(pyramidSize, cubeWidth, cubeHeight, colors[0], colors[2], colors[1], revertible);

	pyramid->AddComponent(pLevelComponent);
	Add(pyramid);

	const float plateWidth = cubeWidth / 2.f;
	const float plateheight = cubeHeight / 2.f;
	
	for (size_t idx = 0; idx < plateRows.size(); ++idx)
	{
		//Test Plate Left
		auto leftPlate = std::make_shared<GameObject>();
		auto* pPlateLeftComp = new PlateComponent(pLevelComponent, plateRows[idx], Side::left);
		auto* pPlateLeftRenderComp = new RenderComponent("Plate.png");
		leftPlate->AddComponent(pPlateLeftComp);
		leftPlate->AddComponent(pPlateLeftRenderComp);
		pPlateLeftRenderComp->SetDimensions(plateWidth, plateheight);
		pPlateLeftComp->Initialize();
		Add(leftPlate);

		//Test Plate Right
		auto rightPlate = std::make_shared<GameObject>();
		auto* pPlateRightComp = new PlateComponent(pLevelComponent, plateRows[idx], Side::right);
		auto* pPlateRightRenderComp = new RenderComponent("Plate.png");
		rightPlate->AddComponent(pPlateRightComp);
		rightPlate->AddComponent(pPlateRightRenderComp);
		pPlateRightRenderComp->SetDimensions(plateWidth, plateheight);
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
	
	//Players
	auto pPlayerObserver = std::make_shared<PlayerObserver>();

	//Player HUD
	const auto hudFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//Lives remaining
	auto pLives = std::make_shared<GameObject>();
	auto* pLivesComponent = new LivesComponent(qbertLives);
	const std::string livesString = "Remaining lives: " + std::to_string(pLivesComponent->GetLivesRemaining());
	auto* pLivesText = new TextComponent(livesString, hudFont);
	auto* pLivesSubjectComponent = new SubjectComponent();
	pLives->AddComponent(pLivesText);
	pLives->AddComponent(pLivesComponent);
	pLives->AddComponent(pLivesSubjectComponent);
	pLives->SetPosition(10, 120);
	Add(pLives);
	pLivesSubjectComponent->AddObserver(pPlayerObserver);

	//Score
	auto pScore = std::make_shared<GameObject>();
	auto* pScoreComponent = new ScoreComponent();
	const std::string player1ScoreString = "Score: " + std::to_string(pScoreComponent->GetScore());
	auto* pScoreText = new TextComponent(player1ScoreString, hudFont);
	auto* pScoreSubjectComponent = new SubjectComponent();
	pScore->AddComponent(pScoreText);
	pScore->AddComponent(pScoreComponent);
	pScore->AddComponent(pScoreSubjectComponent);
	pScore->SetPosition(10, 150);
	Add(pScore);
	pScoreSubjectComponent->AddObserver(pPlayerObserver);

	//Player
	auto QBert = std::make_shared<GameObject>();
	auto* pQBertComponent = new QBertComponent(pLevelComponent, jumpCooldownQBert, pLivesComponent, pScoreComponent);
	auto* pQBertRenderComponent = new RenderComponent("Qbert.png");
	auto* pQBertSubjectComponent = new SubjectComponent();
	QBert->AddComponent(pQBertComponent);
	QBert->AddComponent(pQBertRenderComponent);
	QBert->AddComponent(pQBertSubjectComponent);
	pQBertComponent->ChangeCube(pLevelComponent->GetTopCube(), false, false, false);
	Add(QBert);
	pQBertSubjectComponent->AddObserver(pPlayerObserver);
	pQBertRenderComponent->SetDimensions(cubeWidth * 0.75f, cubeHeight * 0.75f);
	
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