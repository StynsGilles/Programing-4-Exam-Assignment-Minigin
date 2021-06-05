#pragma once
#include <Scene.h>

namespace dae
{
	class MainMenuScene final : public Scene
	{
	public:
		explicit MainMenuScene(const std::string& name);
		
		void Initialize() override;

		MainMenuScene(const MainMenuScene& other) = delete;
		MainMenuScene(MainMenuScene&& other) = delete;
		MainMenuScene& operator=(const MainMenuScene& other) = delete;
		MainMenuScene& operator=(MainMenuScene&& other) = delete;
	protected:
	};
}