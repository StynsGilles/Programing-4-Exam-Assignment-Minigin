#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
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

	ServiceLocator::RegisterSoundSystem(new SoundSystem());
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

	InitPlayers(scene);
}

void dae::Minigin::InitPlayers(Scene& scene) const
{
	auto& renderer = Renderer::GetInstance();
	
	auto pPlayerObserver = std::make_shared<dae::PlayerObserver>();
	
	auto qBert = std::make_shared<GameObject>();
	auto* pQBertIndexComponent = new PlayerIndexComponent(1);
	auto* pQBertRenderComponent = new RenderComponent();
	auto* pQBertSubjectComponent = new SubjectComponent();
	auto* pQBertHealthComponent = new HealthComponent();
	auto* pQBertScoreComponent = new ScoreComponent();
	pQBertRenderComponent->SetTexture("Qbert.png");
	pQBertSubjectComponent->addObserver(pPlayerObserver);
	qBert->AddComponent(pQBertIndexComponent);
	qBert->AddComponent(pQBertRenderComponent);
	qBert->AddComponent(pQBertSubjectComponent);
	qBert->AddComponent(pQBertHealthComponent);
	qBert->AddComponent(pQBertScoreComponent);
	renderer.InitPlayerValues(pQBertIndexComponent->GetIndex(), pQBertHealthComponent->GetHealth(), pQBertHealthComponent->GetMaxHealth(), pQBertHealthComponent->GetLivesRemaining(), pQBertScoreComponent->GetScore());
	scene.Add(qBert);

	auto evilQBert = std::make_shared<GameObject>();
	auto* pEvilQBertIndexComponent = new PlayerIndexComponent(2);
	auto* pEvilQBertRenderComponent = new RenderComponent();
	auto* pEvilQBertSubjectComponent = new SubjectComponent();
	auto* pEvilQBertHealthComponent = new HealthComponent();
	auto* pEvilQBertScoreComponent = new ScoreComponent();
	pEvilQBertRenderComponent->SetTexture("evilQbert.png");
	pEvilQBertSubjectComponent->addObserver(pPlayerObserver);
	evilQBert->AddComponent(pEvilQBertIndexComponent);
	evilQBert->AddComponent(pEvilQBertRenderComponent);
	evilQBert->AddComponent(pEvilQBertSubjectComponent);
	evilQBert->AddComponent(pEvilQBertHealthComponent);
	evilQBert->AddComponent(pEvilQBertScoreComponent);
	renderer.InitPlayerValues(pEvilQBertIndexComponent->GetIndex(), pEvilQBertHealthComponent->GetHealth(), pEvilQBertHealthComponent->GetMaxHealth(), pEvilQBertHealthComponent->GetLivesRemaining(), pEvilQBertScoreComponent->GetScore());
	scene.Add(evilQBert);


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