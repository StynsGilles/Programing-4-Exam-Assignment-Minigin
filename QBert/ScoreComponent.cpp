#include "pch.h"
#include "ScoreComponent.h"

#include <GameObject.h>
#include <Observer.h>
#include <SubjectComponent.h>

dae::ScoreComponent::ScoreComponent()
	: BaseComponent()
	, m_Score(0)
{}

dae::ScoreComponent::~ScoreComponent()
{}

void dae::ScoreComponent::Update()
{}

void dae::ScoreComponent::Render() const
{}

void dae::ScoreComponent::SetScore(int score)
{
	m_Score = score;
	m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::IncreaseScore);
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