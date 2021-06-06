#include "pch.h"
#include "LivesComponent.h"
#include "SubjectComponent.h"
#include "GameObject.h"
#include <Observer.h>

dae::LivesComponent::LivesComponent(int maxLives)
	: m_MaxLives(maxLives)
	, m_LivesRemaining(maxLives)
{
}

dae::LivesComponent::~LivesComponent()
{
}

void dae::LivesComponent::Update()
{
}

void dae::LivesComponent::Render() const
{
}

void dae::LivesComponent::SetLives(int lives)
{
	m_LivesRemaining = lives;
	m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::UpdatedLives);
}

void dae::LivesComponent:: LoseLives(int amount)
{
	m_LivesRemaining -= amount;
	m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::PlayerDied);
	if (m_LivesRemaining <= 0)
		m_pObject->Delete();
}

int dae::LivesComponent::GetLivesRemaining() const
{
	return m_LivesRemaining;
}
