#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "Observer.h"
#include "SubjectComponent.h"
#include "GameObject.h"

dae::ScoreComponent::ScoreComponent()
	: BaseComponent()
	, m_Score(0)
{
}

dae::ScoreComponent::~ScoreComponent()
{
}

void dae::ScoreComponent::Update()
{
}

void dae::ScoreComponent::Render() const
{
}

void dae::ScoreComponent::AddToScore(int score)
{
	m_Score += score;
	m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::IncreaseScore);
}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}