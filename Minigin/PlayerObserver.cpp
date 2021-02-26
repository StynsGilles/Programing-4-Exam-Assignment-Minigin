#include "MiniginPCH.h"
#include "PlayerObserver.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PlayerIndexComponent.h"
#include "Renderer.h"
#include "ScoreComponent.h"

dae::PlayerObserver::PlayerObserver()
	: Observer()
{
}

dae::PlayerObserver::~PlayerObserver()
{
}

void dae::PlayerObserver::onNotify(GameObject* entity, Event event)
{
	int index = entity->GetComponent<PlayerIndexComponent>()->GetIndex();
	
	switch (event)
	{
	case Event::PlayerDied:
		std::cout << "PlayerDied" << std::endl;
		Renderer::GetInstance().UpdateLives(index, entity->GetComponent<HealthComponent>()->GetLivesRemaining());
		break;
	case Event::PlayerLostHP:
		std::cout << "Lost hp" << std::endl;
		Renderer::GetInstance().UpdateHealth(index, entity->GetComponent<HealthComponent>()->GetHealth());
		break;
	case Event::IncreaseScore:
		std::cout << "Increasing score" << std::endl;
		Renderer::GetInstance().UpdateScore(index, entity->GetComponent<ScoreComponent>()->GetScore());
		break;
	default:
		break;
	}
}
