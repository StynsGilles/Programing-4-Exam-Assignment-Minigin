#include <MiniginPCH.h>
#include "PlayerObserver.h"
#include <GameObject.h>
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include <TextComponent.h>

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
		UpdateLivesText(pEntity);
		break;
	case Event::PlayerLostHP:
		UpdateHealthText(pEntity);
		break;
	case Event::IncreaseScore:
		UpdateScoreText(pEntity);
		break;
	default:
		break;
	}
}

void dae::PlayerObserver::UpdateHealthText(GameObject* pEntity)
{
	std::cout << "Lost hp" << std::endl;
	auto* healthText = m_HealthObject->GetComponent<TextComponent>();
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
	auto* livesRemainingText = m_LivesObject->GetComponent<TextComponent>();
	auto* healthLivesComp = pEntity->GetComponent<HealthComponent>();
	if (livesRemainingText && healthLivesComp)
	{
		const std::string livesString = "Remaining lives: " + std::to_string(healthLivesComp->GetLivesRemaining());
		livesRemainingText->SetText(livesString);
	}
}

void dae::PlayerObserver::UpdateScoreText(GameObject* pEntity)
{
	std::cout << "Increasing score" << std::endl;
	auto* scoreText = m_ScoreObject->GetComponent<TextComponent>();
	auto* scoreComp = pEntity->GetComponent<ScoreComponent>();
	if (scoreText && scoreComp)
	{
		const std::string scoreString = "Score: " + std::to_string(scoreComp->GetScore());
		scoreText->SetText(scoreString);
	}
}

void dae::PlayerObserver::SetHealthObject(std::shared_ptr<GameObject> pHealth)
{
	m_HealthObject = pHealth;
}

void dae::PlayerObserver::SetLivesObject(std::shared_ptr<GameObject> pLives)
{
	m_LivesObject = pLives;
}

void dae::PlayerObserver::SetScorebject(std::shared_ptr<GameObject> pScore)
{
	m_ScoreObject = pScore;
}