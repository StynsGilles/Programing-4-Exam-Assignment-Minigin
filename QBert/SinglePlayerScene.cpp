#include "pch.h"
#include "SinglePlayerScene.h"
#include "CoilySpawnerComponent.h"
#include "FPSComponent.h"
#include "GameCommands.h"
#include "LevelParser.h"
#include "LivesComponent.h"
#include "PlateComponent.h"
#include "PlayerObserver.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"
#include "SlickAndSamSpawnerComponent.h"
#include "SubjectComponent.h"
#include "TextComponent.h"
#include "UggAndWrongSpawnerComponent.h"

dae::SinglePlayerScene::SinglePlayerScene(const std::string& name, const std::wstring& fileName)
	: BaseLevelScene(name, fileName)
{
	
}

void dae::SinglePlayerScene::Initialize()
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

	LevelParser::LoadLevel(L"../Data/LevelData/" + m_FileName,
		revertible, colors,
		pyramidSize, plateRows,
		qbertLives, jumpCooldownQBert,
		spawnIntervalSlick, jumpCooldownSlick,
		spawnIntervalUgg, jumpCooldownUgg,
		spawnIntervalCoily, jumpCooldownCoily
	);
	
	//Create objects
	auto go = std::make_shared<dae::GameObject>();
	auto* pBackgroundTextureComponent = new RenderComponent();
	pBackgroundTextureComponent->SetTexture("background.jpg");
	go->AddComponent(pBackgroundTextureComponent);
	Add(go);

	go = std::make_shared<dae::GameObject>();
	auto* pLogoTextureComponent = new RenderComponent();
	pLogoTextureComponent->SetTexture("logo.png");
	go->AddComponent(pLogoTextureComponent);
	go->SetPosition(216, 180);
	Add(go);

	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::GameObject>();
	auto* pTextTextureComponent = new RenderComponent();
	auto* pTextInfoComponent = new TextComponent("Programming 4 Assignment", font);
	to->AddComponent(pTextTextureComponent);
	to->AddComponent(pTextInfoComponent);
	to->SetPosition(80, 20);
	Add(to);

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
	auto* pCoilyspawnComponent = new CoilySpawnerComponent(pLevelComponent, spawnIntervalCoily, jumpCooldownCoily);
	pCoilySpawner->AddComponent(pCoilyspawnComponent);
	Add(pCoilySpawner);

	//Players
	auto pPlayerObserver = std::make_shared<PlayerObserver>();

	//Player HUD
	const auto hudFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//Title
	auto pHUDTitle = std::make_shared<GameObject>();
	std::string HUDTitleString = "Player 1";
	auto* pHUDTitleText = new TextComponent(HUDTitleString, hudFont);
	auto* pHUDTitleRender = new RenderComponent();
	pHUDTitle->AddComponent(pHUDTitleText);
	pHUDTitle->AddComponent(pHUDTitleRender);
	pHUDTitle->SetPosition(10, 60);
	Add(pHUDTitle);

	//Lives remaining
	auto pLives = std::make_shared<GameObject>();
	auto* pLivesComponent = new LivesComponent(qbertLives);
	const std::string livesString = "Remaining lives: " + std::to_string(pLivesComponent->GetLivesRemaining());
	auto* pLivesText = new TextComponent(livesString, hudFont);
	auto* pLivesRender = new RenderComponent();
	auto* pLivesSubjectComponent = new SubjectComponent();
	pLives->AddComponent(pLivesText);
	pLives->AddComponent(pLivesRender);
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
	auto* pScoreRender = new RenderComponent();
	auto* pScoreSubjectComponent = new SubjectComponent();
	pScore->AddComponent(pScoreText);
	pScore->AddComponent(pScoreRender);
	pScore->AddComponent(pScoreComponent);
	pScore->AddComponent(pScoreSubjectComponent);
	pScore->SetPosition(10, 150);
	Add(pScore);
	pScoreSubjectComponent->AddObserver(pPlayerObserver);

	//Player 1
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

	//Adding input
	const ActionInfo GoNorthEast{ ControllerButton::Up, SDL_SCANCODE_W, InputState::Up };
	const ActionInfo GoNorthWest{ ControllerButton::Left, SDL_SCANCODE_A, InputState::Up };
	const ActionInfo GoSouthEast{ ControllerButton::Right, SDL_SCANCODE_D, InputState::Up };
	const ActionInfo GoSouthWest{ ControllerButton::Down, SDL_SCANCODE_S, InputState::Up };

	//Player 1
	m_InputManager->AddInput(0, GoNorthEast, new NorthEast(QBert));
	m_InputManager->AddInput(0, GoNorthWest, new NorthWest(QBert));
	m_InputManager->AddInput(0, GoSouthEast, new SouthEast(QBert));
	m_InputManager->AddInput(0, GoSouthWest, new SouthWest(QBert));
}