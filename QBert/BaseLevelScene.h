#pragma once
#include <Scene.h>

#include "GameStructs.h"
#include "LevelComponent.h"

namespace dae
{
	class PlayerObserver;
	class Observer;
	class ScoreComponent;
	class LivesComponent;
	struct LevelCube;
	
	class BaseLevelScene : public Scene
	{
	public:
		explicit BaseLevelScene(const std::string& name, int level);
		~BaseLevelScene();
		
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
		GameRules m_GameRules;
		LevelComponent* m_pPyramid = nullptr;
		
		void LoadLevel();
		void InitializeLevel();
		void CreatePlates();
		void CreatePlate(int plateRow, const Side& side);
		void InitializeSpawners(bool coilyIsPlayer = false);
		void CreatePlayerHUD(const std::shared_ptr<PlayerObserver>& pPlayerObserver, LivesComponent*& pLivesComponent, ScoreComponent*& pScoreComponent);
		std::shared_ptr<GameObject> CreatePlayerObject(LevelCube* startingCube, LivesComponent* pLivesComponent,
			ScoreComponent* pScoreComponent, float jumpCooldownQBert, std::shared_ptr<Observer> pPlayerObserver) const;

	};
}
