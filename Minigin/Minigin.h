#pragma once
struct SDL_Window;
namespace dae
{
	class Font;
	class Renderer;
	class Scene;

	class Minigin final
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();
	private:
		SDL_Window* m_Window{};
	};
}