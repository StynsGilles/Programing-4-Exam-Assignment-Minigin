#include <MiniginPCH.h>
#include "HealthComponent.h"
#include <GameObject.h>
#include <SubjectComponent.h>

dae::HealthComponent::HealthComponent()
	: BaseComponent()
	, m_MaxHealth(3)
	, m_MaxLives(3)
{
	m_CurrentHealth = m_MaxHealth;
	m_LivesRemaining = m_MaxLives;
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

void dae::HealthComponent::Damage(int amount)
{
	m_CurrentHealth -= amount;
	if (m_CurrentHealth>m_MaxHealth)
		m_CurrentHealth = m_MaxHealth;
	if (m_CurrentHealth <= 0)
		LoseLives(1);
	m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::PlayerLostHP);
}

void dae::HealthComponent::LoseLives(int amount)
{
	m_LivesRemaining -= amount;
	m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::PlayerDied);
	if (m_LivesRemaining <= 0)
	{
		m_CurrentHealth = 0;
		m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::PlayerLostHP);
		m_pObject->Delete();
	}
	else
		m_CurrentHealth = m_MaxHealth;
}

int dae::HealthComponent::GetHealth() const
{
	return m_CurrentHealth;
}

int dae::HealthComponent::GetMaxHealth() const
{
	return m_MaxHealth;
}

int dae::HealthComponent::GetLivesRemaining() const
{
	return m_LivesRemaining;
}
