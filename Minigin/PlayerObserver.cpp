#include "MiniginPCH.h"
#include "PlayerObserver.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "imgui.h"
#include "PlayerIndexComponent.h"
#include "Renderer.h"
#include "ScoreComponent.h"

dae::PlayerObserver::PlayerObserver()
	: Observer()
	, BaseComponent()
{
}

dae::PlayerObserver::~PlayerObserver()
{
}

void dae::PlayerObserver::onNotify(GameObject* entity, Event event)
{
	switch (event)
	{
	case Event::PlayerDied:
		std::cout << "PlayerDied" << std::endl;
		m_PlayerLivesRemaining = entity->GetComponent<HealthComponent>()->GetLivesRemaining();
		break;
	case Event::PlayerLostHP:
		std::cout << "Lost hp" << std::endl;
		m_PlayerHealth = entity->GetComponent<HealthComponent>()->GetHealth();
		break;
	case Event::IncreaseScore:
		std::cout << "Increasing score" << std::endl;
		m_PlayerScore = entity->GetComponent<ScoreComponent>()->GetScore();
		break;
	default:
		break;
	}
}

void dae::PlayerObserver::Update()
{
}

void dae::PlayerObserver::Render() const
{
	const std::string playerIndex{ "Player "+std::to_string(m_PlayerIndex) };
	ImGui::Begin(playerIndex.c_str());

	const std::string health{ "Health: " + std::to_string(m_PlayerHealth) + "/" + std::to_string(m_PlayerMaxHealth) };
	ImGui::Text(health.c_str());

	const std::string livesRemaining{ "remaining lives: " + std::to_string(m_PlayerLivesRemaining) };
	ImGui::Text(livesRemaining.c_str());

	const  std::string score{ "Score: " + std::to_string(m_PlayerScore) };
	ImGui::Text(score.c_str());

	ImGui::SetWindowPos({ m_PosX, m_PosY });
	ImGui::End();
}

void dae::PlayerObserver::SetPosition(float x, float y)
{
	m_PosX = x;
	m_PosY = y;
}

void dae::PlayerObserver::InitValues(std::shared_ptr<GameObject> pPlayer)
{
	m_PlayerIndex = pPlayer->GetComponent<PlayerIndexComponent>()->GetIndex();
	auto playerHealth = pPlayer->GetComponent<HealthComponent>();
	m_PlayerHealth = playerHealth->GetHealth();
	m_PlayerMaxHealth = playerHealth->GetMaxHealth();
	m_PlayerLivesRemaining = playerHealth->GetLivesRemaining();
	auto playerScore = pPlayer->GetComponent<ScoreComponent>();
	m_PlayerScore = playerScore->GetScore();
}
