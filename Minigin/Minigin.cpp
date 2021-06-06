#include "MiniginPCH.h"
#include "Minigin.h"

#include <chrono>
#include <functional>
#include <SDL.h>
#include <thread>

#include "GameTime.h"
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SoundSystem.h"

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
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& time = GameTime::GetInstance();

	bool doContinue = true;
	while (doContinue)
	{
		time.Update();

		doContinue = sceneManager.GetCurrentScene()->GetInputManager()->ProcessInput();
		sceneManager.Update();
		sceneManager.RemoveDeadObjects();

		renderer.Render();

		auto sleepTime = duration_cast<duration<float>>(time.GetPreviousTime() + milliseconds(int(time.GetMsPerFrame())) - high_resolution_clock::now());
		this_thread::sleep_for(sleepTime);
	}

	Cleanup();
}