#pragma once
#include <Scene.h>

namespace dae
{
	class BaseLevelScene : public Scene
	{
	public:
		explicit BaseLevelScene(const std::string& name, int level);

		void Initialize() override;
		int GetLevel() const;
		static int GetMaxLevel();
		bool IsLastLevel() const;
		
		BaseLevelScene(const BaseLevelScene& other) = delete;
		BaseLevelScene(BaseLevelScene&& other) = delete;
		BaseLevelScene& operator=(const BaseLevelScene& other) = delete;
		BaseLevelScene& operator=(BaseLevelScene&& other) = delete;
	protected:
		int m_Level;
		static const int m_MaxLevel = 3;
	};
}