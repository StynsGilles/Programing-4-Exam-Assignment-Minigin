#include "pch.h"
#include "QBertComponent.h"
#include <SDL_render.h>

#include "EntityComponent.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "SlickAndSamComponent.h"

dae::QBertComponent::QBertComponent()
{
}

dae::QBertComponent::~QBertComponent()
{
}

void dae::QBertComponent::Update()
{
}

void dae::QBertComponent::Render() const
{
}

void dae::QBertComponent::ChangeCube(LevelCube* pNewCube, bool fellOf, bool positiveChange, bool isOccupied)
{
	if (m_pCurrentCube)
		m_pCurrentCube->entity = nullptr;

	m_pCurrentCube = pNewCube;
	if (m_pCurrentCube)
	{
		if (isOccupied)
		{
			auto* pEntityComp = m_pCurrentCube->entity->GetComponent<EntityComponent>();

			if (dynamic_cast<SlickAndSamComponent*>(pEntityComp))
			{
				KillGreen();

				m_pCurrentCube->entity->Delete();
			}
			else
				m_pObject->GetComponent<LivesComponent>()->LoseLives(1);
		}

		if (fellOf)
			m_pObject->GetComponent<LivesComponent>()->LoseLives(1);

		if (positiveChange)
			m_pObject->GetComponent<ScoreComponent>()->AddToScore(m_ScorePerCubeChange);

		m_pCurrentCube->entity = m_pObject;

		SDL_Rect dst;
		SDL_QueryTexture(pNewCube->pCubeTextures[pNewCube->stage]->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

		glm::vec3 pos = m_pCurrentCube->position;
		pos.x += (float)dst.w / 3.f;
		pos.y -= 5.f;

		UpdatePosition(pos);
	}
}

dae::LevelCube* dae::QBertComponent::GetCurrentCube() const
{
	return m_pCurrentCube;
}

void dae::QBertComponent::KillGreen() const
{
	m_pObject->GetComponent<ScoreComponent>()->AddToScore(m_ScoreSlAndSaDefeat);
}

void dae::QBertComponent::FinishLevel() const
{
	std::cout << "Congratulations!" << std::endl;
}

void dae::QBertComponent::UpdatePosition(const glm::vec3& nextPosition)
{
	m_pObject->SetPosition(nextPosition.x, nextPosition.y);
}
