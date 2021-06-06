#include "pch.h"
#include "CoopScene.h"

#include <TextComponent.h>

#include "GameCommands.h"
#include "LevelParser.h"
#include "LivesComponent.h"
#include "PlayerObserver.h"
#include "ScoreComponent.h"

dae::CoopScene::CoopScene(const std::string& name, int level)
	: BaseLevelScene(name, level)
{}

dae::CoopScene::~CoopScene()
{}

void dae::CoopScene::Initialize()
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

	const int maxRowCol = m_pPyramid->GetPyramidSize() - 1;
	
	//Player 1
	const auto pQBert = CreatePlayerObject(m_pPyramid->GetCube(maxRowCol), pLivesComponent,
		pScoreComponent, m_GameRules.JumpCooldownQBert, pPlayerObserver);
	Add(pQBert);

	//Player 2
	const auto pQBertPlayer2 = CreatePlayerObject(m_pPyramid->GetCube(maxRowCol, maxRowCol), pLivesComponent,
		pScoreComponent, m_GameRules.JumpCooldownQBert, pPlayerObserver);
	Add(pQBertPlayer2);

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

	//Player 2
	const ActionInfo GoNorthEastP2{ ControllerButton::Up, SDL_SCANCODE_UP, InputState::Up };
	const ActionInfo GoNorthWestP2{ ControllerButton::Left, SDL_SCANCODE_LEFT, InputState::Up };
	const ActionInfo GoSouthEastP2{ ControllerButton::Right, SDL_SCANCODE_RIGHT, InputState::Up };
	const ActionInfo GoSouthWestP2{ ControllerButton::Down, SDL_SCANCODE_DOWN, InputState::Up };

	m_InputManager->AddInput(1, GoNorthEastP2, new NorthEast(pQBertPlayer2));
	m_InputManager->AddInput(1, GoNorthWestP2, new NorthWest(pQBertPlayer2));
	m_InputManager->AddInput(1, GoSouthEastP2, new SouthEast(pQBertPlayer2));
	m_InputManager->AddInput(1, GoSouthWestP2, new SouthWest(pQBertPlayer2));

}
