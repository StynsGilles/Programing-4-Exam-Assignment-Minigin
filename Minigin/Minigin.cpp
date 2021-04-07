#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <functional>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "SubjectComponent.h"
#include "HealthComponent.h"
#include "PlayerIndexComponent.h"
#include "PlayerObserver.h"
#include "ScoreComponent.h"
#include "SoundSystem.h"
#include "ServiceLocator.h"
#include "SoundQueue.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	_putenv("SDL_AUDIODRIVER=DirectSound");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	 ServiceLocator::RegisterSoundSystem(std::make_unique<SoundSystem>());
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	//Create observers

	//Create objects
	auto go = std::make_shared<GameObject>();
	RenderComponent* pBackgroundTextureComponent = new RenderComponent();
	pBackgroundTextureComponent->SetTexture("background.jpg");
	go->AddComponent(pBackgroundTextureComponent);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	RenderComponent* pLogoTextureComponent = new RenderComponent();
	pLogoTextureComponent->SetTexture("logo.png");
	go->AddComponent(pLogoTextureComponent);
	go->SetPosition(216, 180);
	scene.Add(go);

	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<GameObject>();
	RenderComponent* pTextTextureComponent = new RenderComponent();
	TextComponent* pTextInfoComponent = new TextComponent("Programming 4 Assignment", font);
	to->AddComponent(pTextTextureComponent);
	to->AddComponent(pTextInfoComponent);
	to->SetPosition(80, 20);
	scene.Add(to);

	const auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fps = std::make_shared<GameObject>();
	auto* pFPSTextureComponent = new RenderComponent();
	TextComponent* pTextComponent = new TextComponent("00 fps", fpsFont);
	FPSComponent* pFPSComponent = new FPSComponent(pTextComponent);
	pTextComponent->SetColor(SDL_Color{ 255, 255, 0 });
	fps->AddComponent(pFPSTextureComponent);
	fps->AddComponent(pTextComponent);
	fps->AddComponent(pFPSComponent);
	scene.Add(fps);

	InitPlayers(scene, font);
}

void dae::Minigin::InitPlayers(Scene& scene, const shared_ptr<Font> font) const
{
	//Player 1
	auto pPlayer1Observer = std::make_shared<dae::PlayerObserver>();
	
	auto qBert = std::make_shared<GameObject>();
	auto* pQBertIndexComponent = new PlayerIndexComponent(1);
	auto* pQBertRenderComponent = new RenderComponent();
	auto* pQBertSubjectComponent = new SubjectComponent();
	auto* pQBertHealthComponent = new HealthComponent();
	auto* pQBertScoreComponent = new ScoreComponent();
	pQBertRenderComponent->SetTexture("Qbert.png");
	pQBertRenderComponent->SetDimensions(50, 50);
	pQBertSubjectComponent->AddObserver(pPlayer1Observer);
	qBert->AddComponent(pQBertIndexComponent);
	qBert->AddComponent(pQBertRenderComponent);
	qBert->AddComponent(pQBertSubjectComponent);
	qBert->AddComponent(pQBertHealthComponent);
	qBert->AddComponent(pQBertScoreComponent);
	qBert->SetPosition(50, 200);
	scene.Add(qBert);

	//Player 1 HUD
	//Title
	auto player1HUDTitle = std::make_shared<GameObject>();
	std::string player1HUDTitleString = "Player 1";
	auto* pPlayer1HUDTitleText = new TextComponent(player1HUDTitleString, font);
	auto* pPlayer1HUDTitleRender = new RenderComponent();
	player1HUDTitle->AddComponent(pPlayer1HUDTitleText);
	player1HUDTitle->AddComponent(pPlayer1HUDTitleRender);
	player1HUDTitle->SetPosition(10, 50);
	scene.Add(player1HUDTitle);
	
	//Health
	auto player1Health = std::make_shared<GameObject>();
	std::string player1HealthString = "Health: " + std::to_string(pQBertHealthComponent->GetHealth()) + "/" + std::to_string(pQBertHealthComponent->GetMaxHealth());
	auto* pPlayer1HealthText = new TextComponent(player1HealthString, font);
	auto* pPlayer1HealthRender = new RenderComponent();
	player1Health->AddComponent(pPlayer1HealthText);
	player1Health->AddComponent(pPlayer1HealthRender);
	player1Health->SetPosition(10, 80);
	scene.Add(player1Health);
	pPlayer1Observer->SetHealthObject(player1Health);
	
	//Lives remaining
	auto player1Lives = std::make_shared<GameObject>();
	const std::string player1LivesString = "Remaining lives: " + std::to_string(pQBertHealthComponent->GetLivesRemaining());
	auto* pPlayer1LivesText = new TextComponent(player1LivesString, font);
	auto* pPlayer1LivesRender = new RenderComponent();
	player1Lives->AddComponent(pPlayer1LivesText);
	player1Lives->AddComponent(pPlayer1LivesRender);
	player1Lives->SetPosition(10, 110);
	scene.Add(player1Lives);
	pPlayer1Observer->SetLivesObject(player1Lives);
	
	//Score
	auto player1Score = std::make_shared<GameObject>();
	const std::string player1ScoreString = "Score: " + std::to_string(pQBertScoreComponent->GetScore());
	auto* pPlayer1ScoreText = new TextComponent(player1ScoreString, font);
	auto* pPlayer1ScoreRender = new RenderComponent();
	player1Score->AddComponent(pPlayer1ScoreText);
	player1Score->AddComponent(pPlayer1ScoreRender);
	player1Score->SetPosition(10, 140);
	scene.Add(player1Score);
	pPlayer1Observer->SetScorebject(player1Score);

	//Player 2
	auto pPlayer2Observer = std::make_shared<dae::PlayerObserver>();
	
	auto evilQBert = std::make_shared<GameObject>();
	auto* pEvilQBertIndexComponent = new PlayerIndexComponent(2);
	auto* pEvilQBertRenderComponent = new RenderComponent();
	auto* pEvilQBertSubjectComponent = new SubjectComponent();
	auto* pEvilQBertHealthComponent = new HealthComponent();
	auto* pEvilQBertScoreComponent = new ScoreComponent();
	pEvilQBertRenderComponent->SetTexture("evilQbert.png");
	pEvilQBertRenderComponent->SetDimensions(50, 50);
	pEvilQBertSubjectComponent->AddObserver(pPlayer2Observer);
	evilQBert->AddComponent(pEvilQBertIndexComponent);
	evilQBert->AddComponent(pEvilQBertRenderComponent);
	evilQBert->AddComponent(pEvilQBertSubjectComponent);
	evilQBert->AddComponent(pEvilQBertHealthComponent);
	evilQBert->AddComponent(pEvilQBertScoreComponent);
	evilQBert->SetPosition(400, 200);
	scene.Add(evilQBert);

	//Player 2 HUD
	//Title
	auto player2HUDTitle = std::make_shared<GameObject>();
	std::string player2HUDTitleString = "Player 2";
	auto* pPlayer2HUDTitleText = new TextComponent(player2HUDTitleString, font);
	auto* pPlayer2HUDTitleRender = new RenderComponent();
	player2HUDTitle->AddComponent(pPlayer2HUDTitleText);
	player2HUDTitle->AddComponent(pPlayer2HUDTitleRender);
	player2HUDTitle->SetPosition(400, 50);
	scene.Add(player2HUDTitle);

	//Health
	auto player2Health = std::make_shared<GameObject>();
	std::string player2HealthString = "Health: " + std::to_string(pEvilQBertHealthComponent->GetHealth()) + "/" + std::to_string(pEvilQBertHealthComponent->GetMaxHealth());
	auto* pPlayer2HealthText = new TextComponent(player2HealthString, font);
	auto* pPlayer2HealthRender = new RenderComponent();
	player2Health->AddComponent(pPlayer2HealthText);
	player2Health->AddComponent(pPlayer2HealthRender);
	player2Health->SetPosition(400, 80);
	scene.Add(player2Health);
	pPlayer2Observer->SetHealthObject(player2Health);
	
	//Lives remaining
	auto player2Lives = std::make_shared<GameObject>();
	const std::string player2LivesString = "Remaining lives: " + std::to_string(pEvilQBertHealthComponent->GetLivesRemaining());
	auto* pPlayer2LivesText = new TextComponent(player2LivesString, font);
	auto* pPlayer2LivesRender = new RenderComponent();
	player2Lives->AddComponent(pPlayer2LivesText);
	player2Lives->AddComponent(pPlayer2LivesRender);
	player2Lives->SetPosition(400, 110);
	scene.Add(player2Lives);
	pPlayer2Observer->SetLivesObject(player2Lives);

	//Score
	auto player2Score = std::make_shared<GameObject>();
	const std::string player2ScoreString = "Score: " + std::to_string(pEvilQBertScoreComponent->GetScore());
	auto* pPlayer2ScoreText = new TextComponent(player2ScoreString, font);
	auto* pPlayer2ScoreRender = new RenderComponent();
	player2Score->AddComponent(pPlayer2ScoreText);
	player2Score->AddComponent(pPlayer2ScoreRender);
	player2Score->SetPosition(400, 140);
	scene.Add(player2Score);
	pPlayer2Observer->SetScorebject(player2Score);
	
	//Adding input
	auto& input = InputManager::GetInstance();

	const ActionInfo killQbertAction{ ControllerButton::ButtonA, SDL_SCANCODE_1, InputState::Up };
	const ActionInfo damageQbertAction{ ControllerButton::ButtonB, SDL_SCANCODE_2, InputState::Up };
	const ActionInfo awardScoreAction{ ControllerButton::ButtonX, SDL_SCANCODE_3, InputState::Up };

	//Player 1
	input.AddInput(0, killQbertAction, new Kill(qBert));
	input.AddInput(0, damageQbertAction, new Damage(qBert));
	input.AddInput(0, awardScoreAction, new Score(qBert));

	//Player 2
	input.AddInput(1, killQbertAction, new Kill(evilQBert));
	input.AddInput(1, damageQbertAction, new Damage(evilQBert));
	input.AddInput(1, awardScoreAction, new Score(evilQBert));
}


void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SoundQueue::GetInstance().StopRunning();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	 
	LoadGame();
	{
		//explain how to play the game
		std::cout << "Welcome to QBert! " << std::endl;
		std::cout << "This game can be played with 2 players and the controls are as follows:" << std::endl;
		std::cout << "A: make your QBert lose a life, B: Make your QBert lose 1 hit point, X: Score some points" << std::endl;
		std::cout << "Player 1 can also use respectively 1, 2 and 3 on the keyboard to do the same thing." << std::endl;
		
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();
		auto& soundQueue = SoundQueue::GetInstance();

		std::thread soundThread(std::bind(&SoundQueue::ProcessQueue, &soundQueue));
		soundThread.detach();
		
		bool doContinue = true;
		while (doContinue)
		{
			time.Update();
			
			doContinue = input.ProcessInput();
			sceneManager.Update();
			sceneManager.RemoveDeadObjects();

			renderer.Render();
			
			auto sleepTime = duration_cast<duration<float>>(time.GetPreviousTime() + milliseconds(int(time.GetMsPerFrame())) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}
	Cleanup();
}