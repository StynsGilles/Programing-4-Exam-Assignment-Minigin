#pragma once
struct SDL_Window;
namespace dae
{
	class Font;
	class Renderer;
	class Scene;

	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
	private:
		void InitPlayers(Scene& scene) const;
		SDL_Window* m_Window{};
	};
}