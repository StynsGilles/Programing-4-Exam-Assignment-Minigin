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

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
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
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

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
	TextComponent* pTextInfoComponent = new TextComponent("Programming 4 Assignment", font, pTextTextureComponent);
	to->AddComponent(pTextTextureComponent);
	to->AddComponent(pTextInfoComponent);
	to->SetPosition(80, 20);
	scene.Add(to);

	const auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fps = std::make_shared<GameObject>();
	auto* pFPSTextureComponent = new RenderComponent();
	TextComponent* pTextComponent = new TextComponent("00 fps", fpsFont, pFPSTextureComponent);
	FPSComponent* pFPSComponent = new FPSComponent(pTextComponent);
	pTextComponent->SetColor(SDL_Color{ 255, 255, 0 });
	fps->AddComponent(pFPSTextureComponent);
	fps->AddComponent(pTextComponent);
	fps->AddComponent(pFPSComponent);
	scene.Add(fps);
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
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();
		
		std::cout << "Change fps with the num pad : '1' for 144 fps, '2' for 60 fps, '3' for 30 fps." << std::endl;

		bool doContinue = true;
		float lag = 0.f;
		while (doContinue)
		{
			time.Update();
			const float elapsedSec = time.GetDeltaTime();
			lag += elapsedSec;
			
			doContinue = input.ProcessInput();

			const float msPerFrame = (float)time.GetMsPerFrame() / 1000.f;
			while (lag >= msPerFrame)
			{
				sceneManager.Update();
				lag -= msPerFrame;
			}
			
			renderer.Render();
			auto sleepTime = duration_cast<duration<float>>(time.GetPreviousTime() + milliseconds(int(time.GetMsPerFrame())) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
