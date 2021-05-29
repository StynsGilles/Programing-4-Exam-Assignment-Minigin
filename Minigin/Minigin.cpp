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
#include "GameTime.h"
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

	std::srand(static_cast<unsigned int>(time(nullptr)));
	
	Renderer::GetInstance().Init(m_Window);
	dae::ResourceManager::GetInstance().Init("../Data/");
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
	//explain how to play the game
	std::cout << "Welcome to QBert! " << std::endl;
	std::cout << "This game can be played with 2 players and the controls are as follows:" << std::endl;
	std::cout << "A: make your QBert lose a life, B: Make your QBert lose 1 hit point, X: Score some points" << std::endl;
	std::cout << "Player 1 can also use respectively 1, 2 and 3 on the keyboard to do the same thing." << std::endl;

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = GameTime::GetInstance();
	//ServiceLocator::GetSoundSystem()->PlayMusic("../Data/Sounds/Menu.wav");

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

	Cleanup();
}