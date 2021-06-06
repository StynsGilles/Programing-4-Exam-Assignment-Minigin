#include "pch.h"
#include "PlayerObserver.h"

#include <GameObject.h>
#include <Scene.h>
#include <SceneManager.h>
#include <TextComponent.h>

#include "BaseLevelScene.h"
#include "LevelComponent.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"

dae::PlayerObserver::PlayerObserver()
	: Observer()
{}

dae::PlayerObserver::~PlayerObserver()
{}

void dae::PlayerObserver::onNotify(GameObject* pEntity, Event event)
{
	switch (event)
	{
	case Event::PlayerDied:
	{
		const auto pScene = SceneManager::GetInstance().GetCurrentScene();
		auto* pLevel = pScene->GetComponentOfType<LevelComponent>();
		pLevel->ClearBoard();
		UpdateLivesText(pEntity);
	}
		break;
	case Event::PlayerLostHP:
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

void dae::PlayerObserver::UpdateLivesText(GameObject* pEntity) const
{
	auto* pLivesRemainingText = pEntity->GetComponent<TextComponent>();
	auto* pLivesComp = pEntity->GetComponent<LivesComponent>();
	if (pLivesRemainingText && pLivesComp)
	{
		const std::string livesString = "Remaining lives: " + std::to_string(pLivesComp->GetLivesRemaining());
		pLivesRemainingText->SetText(livesString);
	}
}

void dae::PlayerObserver::UpdateScoreText(GameObject* pEntity) const
{
	auto* scoreText = pEntity->GetComponent<TextComponent>();
	auto* scoreComp = pEntity->GetComponent<ScoreComponent>();
	if (scoreText && scoreComp)
	{
		const std::string scoreString = "Score: " + std::to_string(scoreComp->GetScore());
		scoreText->SetText(scoreString);
	}
}

void dae::PlayerObserver::HandleFinishedLevel() const
{
	const auto pScene = SceneManager::GetInstance().GetCurrentScene();
	const auto pLevelScene = std::dynamic_pointer_cast<BaseLevelScene>(pScene);

	if (pLevelScene)
	{
		if (!pLevelScene->IsLastLevel())
		{
			auto* pCurrentLivesComp = pLevelScene->GetComponentOfType<LivesComponent>();
			auto* pCurrentScoreComp = pLevelScene->GetComponentOfType<ScoreComponent>();
			
			const auto pNextScene = SceneManager::GetInstance().NextScene();

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