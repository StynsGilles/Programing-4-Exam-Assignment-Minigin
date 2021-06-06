#include "pch.h"
#include "SinglePlayerScene.h"

#include <TextComponent.h>

#include "GameCommands.h"
#include "LevelParser.h"
#include "LivesComponent.h"
#include "PlayerObserver.h"
#include "ScoreComponent.h"

dae::SinglePlayerScene::SinglePlayerScene(const std::string& name, int level)
	: BaseLevelScene(name, level)
{}

dae::SinglePlayerScene::~SinglePlayerScene()
{}

void dae::SinglePlayerScene::Initialize()
{
	BaseLevelScene::Initialize();

	//Enemies
	InitializeSpawners();
	
	//Players
	const auto pPlayerObserver = std::make_shared<PlayerObserver>();

	//Player HUD
	LivesComponent* pLivesComponent = nullptr;
	ScoreComponent* pScoreComponent = nullptr;
	CreatePlayerHUD(pPlayerObserver, pLivesComponent, pScoreComponent);

	//Player 1
	const auto pQBert = CreatePlayerObject(m_pPyramid->GetTopCube(), pLivesComponent,
		pScoreComponent, m_GameRules.JumpCooldownQBert, pPlayerObserver);
	Add(pQBert);
	
	//Adding input
	const ActionInfo GoNorthEast{ ControllerButton::Up, SDL_SCANCODE_W, InputState::Up };
	const ActionInfo GoNorthWest{ ControllerButton::Left, SDL_SCANCODE_A, InputState::Up };
	const ActionInfo GoSouthEast{ ControllerButton::Right, SDL_SCANCODE_D, InputState::Up };
	const ActionInfo GoSouthWest{ ControllerButton::Down, SDL_SCANCODE_S, InputState::Up };

	//Player 1
	m_InputManager->AddInput(0, GoNorthEast, new NorthEast(pQBert));
	m_InputManager->AddInput(0, GoNorthWest, new NorthWest(pQBert));
	m_InputManager->AddInput(0, GoSouthEast, new SouthEast(pQBert));
	m_InputManager->AddInput(0, GoSouthWest, new SouthWest(pQBert));
}