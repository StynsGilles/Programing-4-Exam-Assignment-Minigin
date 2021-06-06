#include "pch.h"
#include "PlayerObserver.h"
#include <GameObject.h>
#include "HealthComponent.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include <TextComponent.h>
#include "LevelComponent.h"
#include <Scene.h>
#include <SceneManager.h>
#include "BaseLevelScene.h"

dae::PlayerObserver::PlayerObserver()
	: Observer()
{
}

dae::PlayerObserver::~PlayerObserver()
{
}

void dae::PlayerObserver::onNotify(GameObject* pEntity, Event event)
{
	switch (event)
	{
	case Event::PlayerDied:
	{
		auto scene = SceneManager::GetInstance().GetCurrentScene();
		auto level = scene->GetComponentOfType<LevelComponent>();
		level->ClearBoard();
		UpdateLivesText(pEntity);
	}
		break;
	case Event::PlayerLostHP:
		UpdateHealthText(pEntity);
		break;
	case Event::IncreaseScore:
		UpdateScoreText(pEntity);
		break;
	case Event::LevelFinished:
		HandleFinishedLevel();
		break;
	case Event::UpdatedLives:
		UpdateLivesText(pEntity);
		break;
	default:
		break;
	}
}

void dae::PlayerObserver::UpdateHealthText(GameObject* pEntity)
{
	std::cout << "Lost hp" << std::endl;
	auto* healthText = pEntity->GetComponent<TextComponent>();
	auto* healthComp = pEntity->GetComponent<HealthComponent>();
	if (healthText && healthComp)
	{
		const std::string healthString = "Health: " + std::to_string(healthComp->GetHealth()) + "/" + std::to_string(healthComp->GetMaxHealth());
		healthText->SetText(healthString);
	}
}

void dae::PlayerObserver::UpdateLivesText(GameObject* pEntity)
{
	std::cout << "PlayerDied" << std::endl;
	auto* pLivesRemainingText = pEntity->GetComponent<TextComponent>();
	auto* pLivesComp = pEntity->GetComponent<LivesComponent>();
	if (pLivesRemainingText && pLivesComp)
	{
		const std::string livesString = "Remaining lives: " + std::to_string(pLivesComp->GetLivesRemaining());
		pLivesRemainingText->SetText(livesString);
	}
}

void dae::PlayerObserver::UpdateScoreText(GameObject* pEntity)
{
	std::cout << "Increasing score" << std::endl;
	auto* scoreText = pEntity->GetComponent<TextComponent>();
	auto* scoreComp = pEntity->GetComponent<ScoreComponent>();
	if (scoreText && scoreComp)
	{
		const std::string scoreString = "Score: " + std::to_string(scoreComp->GetScore());
		scoreText->SetText(scoreString);
	}
}

void dae::PlayerObserver::HandleFinishedLevel()
{
	auto pScene = SceneManager::GetInstance().GetCurrentScene();
	
	auto pLevelScene = std::dynamic_pointer_cast<BaseLevelScene>(pScene);

	if (pLevelScene)
	{
		if (!pLevelScene->IsLastLevel())
		{
			auto* pCurrentLivesComp = pLevelScene->GetComponentOfType<LivesComponent>();
			auto* pCurrentScoreComp = pLevelScene->GetComponentOfType<ScoreComponent>();
			
			auto pNextScene = SceneManager::GetInstance().NextScene();

			auto* pNextLivesComp = pNextScene->GetComponentOfType<LivesComponent>();
			auto* pNextScoreComp = pNextScene->GetComponentOfType<ScoreComponent>();
			if (pCurrentLivesComp && pNextLivesComp)
				pNextLivesComp->SetLives(pCurrentLivesComp->GetLivesRemaining());

			if (pCurrentScoreComp && pNextScoreComp)
				pNextScoreComp->SetScore(pCurrentScoreComp->GetScore());
		}
		else
			SceneManager::GetInstance().SetActiveScene("MainMenu");
	}
}