#pragma once
#include <Scene.h>

namespace dae
{
	class LevelScene final : public Scene
	{
	public:
		explicit LevelScene(const std::string& name);
		
		void Initialize() override;
		
		LevelScene(const LevelScene& other) = delete;
		LevelScene(LevelScene&& other) = delete;
		LevelScene& operator=(const LevelScene& other) = delete;
		LevelScene& operator=(LevelScene&& other) = delete;
	private:
	};
}



