#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>

#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

int dae::Renderer::GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	SceneManager::GetInstance().Render();
	
	RenderHUD();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::InitPlayerValues(int index, int curHealth, int maxHealth, int lives, int score)
{
	switch (index)
	{
	case 1:
		m_Player1Health = curHealth;
		m_Player1MaxHealth = maxHealth;
		m_Player1LivesRemaining = lives;
		m_Player1Score = score;
		break;
	case 2:
		break;
	default:
		break;
	}
}

void dae::Renderer::UpdateLives(int index, int lives)
{
	switch (index)
	{
	case 1:
		m_Player1LivesRemaining = lives;
		break;
	case 2:
		break;
	default:
		break;
	}
}

void dae::Renderer::UpdateHealth(int index, int health)
{
	switch (index)
	{
	case 1:
		m_Player1Health = health;
		break;
	case 2:
		break;
	default:
		break;
	}
}

void dae::Renderer::UpdateScore(int index, int score)
{
	switch (index)
	{
	case 1:
		m_Player1Score = score;
		break;
	case 2:
		break;
	default:
		break;
	}
}

void dae::Renderer::RenderHUD() const
{
	ImGui::Begin("Options");
	ImGui::SetWindowPos({ 50.f, 200.f });
	if (ImGui::Button("single player", { 200.f, 50.f }))
	{
		std::cout << "Starting single player game" << std::endl;
	}
	if (ImGui::Button("co-op", { 200.f, 50.f }))
	{
		std::cout << "Starting co-op game" << std::endl;
	};
	if (ImGui::Button("versus", { 200.f, 50.f }))
	{
		std::cout << "Starting versus game" << std::endl;
	}
	ImGui::End();

	std::string playerIndex{ "Player 1" };
	ImGui::Begin(playerIndex.c_str());

	std::string health{ "Health: " + std::to_string(m_Player1Health) + "/" + std::to_string(m_Player1MaxHealth) };
	ImGui::Text(health.c_str());

	std::string livesRemaining{ "remaining lives: " + std::to_string(m_Player1LivesRemaining) };
	ImGui::Text(livesRemaining.c_str());

	std::string score{ "Score: " + std::to_string(m_Player1Score) };
	ImGui::Text(score.c_str());
	
	ImGui::SetWindowPos({ 10.f, 50.f });
	ImGui::End();
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
