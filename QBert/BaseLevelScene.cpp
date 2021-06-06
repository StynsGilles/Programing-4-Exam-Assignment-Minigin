#include "pch.h"
#include "BaseLevelScene.h"

#include <FPSComponent.h>
#include <RenderComponent.h>
#include <ResourceManager.h>
#include <SubjectComponent.h>
#include <TextComponent.h>
#include <utility>

#include "CoilySpawnerComponent.h"
#include "LevelComponent.h"
#include "LevelParser.h"
#include "LivesComponent.h"
#include "PlateComponent.h"
#include "PlayerObserver.h"
#include "QBertComponent.h"
#include "ScoreComponent.h"
#include "SlickAndSamSpawnerComponent.h"
#include "UggAndWrongSpawnerComponent.h"

dae::BaseLevelScene::BaseLevelScene(const std::string& name, int level)
	: Scene(name)
	, m_Level(level)
{
}

dae::BaseLevelScene::~BaseLevelScene()
{}

void dae::BaseLevelScene::Initialize()
{
	Scene::Initialize();

	//load level from file
	LoadLevel();
	
	//Create objects
	auto pBackGround = std::make_shared<GameObject>();
	auto* pBackgroundTextureComponent = new RenderComponent();
	pBackgroundTextureComponent->SetTexture("background.jpg");
	pBackgroundTextureComponent->SetDimensions(640, 480);
	pBackGround->AddComponent(pBackgroundTextureComponent);
	Add(pBackGround);

	const auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto pFPSTracker = std::make_shared<GameObject>();
	auto* pTextComponent = new TextComponent("00 fps", pFont);
	auto* pFPSComponent = new FPSComponent(pTextComponent);
	pTextComponent->SetColor(SDL_Color{ 255, 255, 0 });
	pFPSTracker->AddComponent(pTextComponent);
	pFPSTracker->AddComponent(pFPSComponent);
	Add(pFPSTracker);

	auto pStageObj = std::make_shared<GameObject>();
	auto* pStageTextComponent = new TextComponent("Level: " + std::to_string(m_Level) + "/" + std::to_string(m_MaxLevel), pFont);
	pStageTextComponent->SetColor(SDL_Color{ 255, 255, 255});
	pStageObj->AddComponent(pStageTextComponent);
	Add(pStageObj);
	pStageObj->SetPosition(0, 30);

	//Level
	InitializeLevel();

	//Create plates
	CreatePlates();
}

int dae::BaseLevelScene::GetLevel() const
{
	return m_Level;
}

int dae::BaseLevelScene::GetMaxLevel()
{
	return m_MaxLevel;
}

bool dae::BaseLevelScene::IsLastLevel() const
{
	return m_Level == m_MaxLevel;
}

void dae::BaseLevelScene::LoadLevel()
{
	m_GameRules = LevelParser::LoadLevel(L"../Data/LevelData/Level" + std::to_wstring(m_Level) + L".json");
}

void dae::BaseLevelScene::InitializeLevel()
{
	//Level
	auto pPyramid = std::make_shared<GameObject>();
	LevelComponent* pLevelComponent = nullptr;
	if (m_GameRules.Colors.size() == 2)
		pLevelComponent = new LevelComponent(m_GameRules.PyramidSize, m_GameRules.CubeWidth, m_GameRules.CubeHeight, m_GameRules.Colors[0], m_GameRules.Colors[1], m_GameRules.Revertible);
	else if (m_GameRules.Colors.size() == 3)
		pLevelComponent = new LevelComponent(m_GameRules.PyramidSize, m_GameRules.CubeWidth, m_GameRules.CubeHeight, m_GameRules.Colors[0], m_GameRules.Colors[2], m_GameRules.Colors[1], m_GameRules.Revertible);
	pPyramid->AddComponent(pLevelComponent);
	Add(pPyramid);
	m_pPyramid = pLevelComponent;
}

void dae::BaseLevelScene::CreatePlates()
{
	for (int plateRow : m_GameRules.PlateRows)
	{
		//Left plate
		CreatePlate(plateRow, Side::left);

		//Right plate
		CreatePlate(plateRow, Side::right);
	}
}

void dae::BaseLevelScene::CreatePlate(int plateRow, const Side& side)
{
	const float plateWidth = m_GameRules.CubeWidth / 2.f;
	const float plateHeight = m_GameRules.CubeHeight / 2.f;
	
	auto pPlate = std::make_shared<GameObject>();
	auto* pPlateComp = new PlateComponent(m_pPyramid, plateRow, side);
	auto* pPlateRenderComp = new RenderComponent("Plate.png");
	pPlate->AddComponent(pPlateComp);
	pPlate->AddComponent(pPlateRenderComp);
	pPlateRenderComp->SetDimensions(plateWidth, plateHeight);
	pPlateComp->Initialize();
	Add(pPlate);
}

void dae::BaseLevelScene::InitializeSpawners(bool coilyIsPlayer)
{
	//Slick and Sam spawner
	auto pSAndSSpawner = std::make_shared<GameObject>();
	auto* pSandSSpawnComponent = new SlickAndSamSpawnerComponent(m_pPyramid, m_GameRules.SpawnIntervalSlick, m_GameRules.JumpCooldownSlick);
	pSAndSSpawner->AddComponent(pSandSSpawnComponent);
	Add(pSAndSSpawner);

	//Ugg + Wrong way spawner
	auto pUAndWSpawner = std::make_shared<GameObject>();
	auto* pUandWSpawnComponent = new UggAndWrongSpawnerComponent(m_pPyramid, m_GameRules.SpawnIntervalUgg, m_GameRules.JumpCooldownUgg);
	pUAndWSpawner->AddComponent(pUandWSpawnComponent);
	Add(pUAndWSpawner);

	//Coily spawner
	auto pCoilySpawner = std::make_shared<GameObject>();
	auto* pCoilyspawnComponent = new CoilySpawnerComponent(m_pPyramid, m_GameRules.SpawnIntervalCoily, m_GameRules.JumpCooldownCoily, coilyIsPlayer);
	pCoilySpawner->AddComponent(pCoilyspawnComponent);
	Add(pCoilySpawner);
}

void dae::BaseLevelScene::CreatePlayerHUD(const std::shared_ptr<PlayerObserver>& pPlayerObserver, LivesComponent*& pLivesComponent, ScoreComponent*& pScoreComponent)
{
	//Player HUD
	const auto hudFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//Lives remaining
	auto pLives = std::make_shared<GameObject>();
	pLivesComponent = new LivesComponent(m_GameRules.QBertLives);
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
	pScoreComponent = new ScoreComponent();
	const std::string player1ScoreString = "Score: " + std::to_string(pScoreComponent->GetScore());
	auto* pScoreText = new TextComponent(player1ScoreString, hudFont);
	auto* pScoreSubjectComponent = new SubjectComponent();
	pScore->AddComponent(pScoreText);
	pScore->AddComponent(pScoreComponent);
	pScore->AddComponent(pScoreSubjectComponent);
	pScore->SetPosition(10, 150);
	Add(pScore);
	pScoreSubjectComponent->AddObserver(pPlayerObserver);
}

std::shared_ptr<dae::GameObject> dae::BaseLevelScene::CreatePlayerObject(LevelCube* startingCube, LivesComponent* pLivesComponent,
	ScoreComponent* pScoreComponent, float jumpCooldownQBert, std::shared_ptr<Observer> pPlayerObserver) const
{
	auto pQBert = std::make_shared<GameObject>();
	auto* pQBertComponent = new QBertComponent(m_pPyramid, jumpCooldownQBert, pLivesComponent, pScoreComponent);
	auto* pQBertRenderComponent = new RenderComponent("Qbert.png");
	auto* pQBertSubjectComponent = new SubjectComponent();
	pQBert->AddComponent(pQBertComponent);
	pQBert->AddComponent(pQBertRenderComponent);
	pQBert->AddComponent(pQBertSubjectComponent);
	pQBertRenderComponent->SetDimensions(m_GameRules.CubeWidth * 0.5f, m_GameRules.CubeHeight * 0.5f);
	pQBertComponent->ChangeCube(startingCube, false, false, false);
	pQBertSubjectComponent->AddObserver(std::move(pPlayerObserver));
	return pQBert;
}
