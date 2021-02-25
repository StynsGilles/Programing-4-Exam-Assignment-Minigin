#include "MiniginPCH.h"
#include "HealthComponent.h"

#include "GameObject.h"
#include "SubjectComponent.h"

dae::HealthComponent::HealthComponent()
	: BaseComponent()
{
}

dae::HealthComponent::~HealthComponent()
{
}

void dae::HealthComponent::Update()
{
}

void dae::HealthComponent::Render() const
{
}

void dae::HealthComponent::Damage(const int& amount)
{
	m_CurrentHealth -= amount;
	if (m_CurrentHealth>m_MaxHealth)
		m_CurrentHealth = m_MaxHealth;
	if (m_CurrentHealth <= 0)
		LoseLives(1);
}

void dae::HealthComponent::LoseLives(const int& amount)
{
	m_LivesRemaining -= amount;
	if (m_LivesRemaining <= 0)
		m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::PlayerDied);
}
