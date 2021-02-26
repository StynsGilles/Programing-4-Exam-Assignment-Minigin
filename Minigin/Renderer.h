#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void InitPlayerValues(int index, int curHealth, int maxHealth, int lives, int score);
		void UpdateLives(int index, int lives);
		void UpdateHealth(int index, int health);
		void UpdateScore(int index, int score);
		void RenderHUD() const;
		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		int GetOpenGLDriverIndex();

		SDL_Window* m_Window{};
		SDL_Renderer* m_Renderer{};

		int m_Player1Health = 0;
		int m_Player1MaxHealth = 0;
		int m_Player1LivesRemaining = 0;
		int m_Player1Score = 0;
		int m_Player2Health = 0;
		int m_Player2MaxHealth = 0;
		int m_Player2LivesRemaining = 0;
		int m_Player2Score = 0;
	};
}

