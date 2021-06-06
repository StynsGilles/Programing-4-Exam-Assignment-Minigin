#include "pch.h"
#include "VersusScene.h"

#include <TextComponent.h>

#include "GameCommands.h"
#include "LevelParser.h"
#include "LivesComponent.h"
#include "PlayerObserver.h"
#include "ScoreComponent.h"

dae::VersusScene::VersusScene(const std::string& name, int level)
	: BaseLevelScene(name, level)
{}

dae::VersusScene::~VersusScene()
{}

void dae::VersusScene::Initialize()
{
	BaseLevelScene::Initialize();

	//Enemies
	InitializeSpawners(true);

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

	const ActionInfo CoilyNorthEast{ ControllerButton::Up, SDL_SCANCODE_UP, InputState::Up };
	const ActionInfo CoilyNorthWest{ ControllerButton::Left, SDL_SCANCODE_LEFT, InputState::Up };
	const ActionInfo CoilySouthEast{ ControllerButton::Right, SDL_SCANCODE_RIGHT, InputState::Up };
	const ActionInfo CoilySouthWest{ ControllerButton::Down, SDL_SCANCODE_DOWN, InputState::Up };
	
	//Player 1
	m_InputManager->AddInput(0, GoNorthEast, new NorthEast(pQBert));
	m_InputManager->AddInput(0, GoNorthWest, new NorthWest(pQBert));
	m_InputManager->AddInput(0, GoSouthEast, new SouthEast(pQBert));
	m_InputManager->AddInput(0, GoSouthWest, new SouthWest(pQBert));

	//Coily
	m_InputManager->AddInput(1, CoilyNorthEast, new NorthEastCoily(std::weak_ptr<GameObject>()));
	m_InputManager->AddInput(1, CoilyNorthWest, new NorthWestCoily(std::weak_ptr<GameObject>()));
	m_InputManager->AddInput(1, CoilySouthEast, new SouthEastCoily(std::weak_ptr<GameObject>()));
	m_InputManager->AddInput(1, CoilySouthWest, new SouthWestCoily(std::weak_ptr<GameObject>()));
}