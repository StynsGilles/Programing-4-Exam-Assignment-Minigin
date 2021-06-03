#include "pch.h"
#include "QBertComponent.h"
#include <SDL_render.h>

#include "CoilyComponent.h"
#include "EntityComponent.h"
#include "GameObject.h"
#include "LivesComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ScoreComponent.h"
#include "SlickAndSamComponent.h"

dae::QBertComponent::QBertComponent(LevelComponent* pPyramid)
	: m_pPyramid(pPyramid)
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
		if (isOccupied && m_pCurrentCube->entity)
		{
			auto* pEntityComp = m_pCurrentCube->entity->GetComponent<EntityComponent>();

			if (dynamic_cast<SlickAndSamComponent*>(pEntityComp))
			{
				KillGreen();
				m_pCurrentCube->entity->Delete();
			}
			else
			{
				if (!m_pCurrentCube->entity->GetMarkedForDeletion())
					m_pObject->GetComponent<LivesComponent>()->LoseLives(1);
			}
		}

		if (fellOf)
			m_pObject->GetComponent<LivesComponent>()->LoseLives(1);

		if (positiveChange)
			FlippedTile();

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
	AwardScore(m_ScoreSlAndSaDefeat);
}

void dae::QBertComponent::KilledCoily() const
{
	AwardScore(m_ScoreCoilyDefeat);
}

void dae::QBertComponent::FlippedTile() const
{
	AwardScore(m_ScorePerCubeChange);
}

void dae::QBertComponent::AwardScore(int amount) const
{
	auto* score = m_pObject->GetComponent<ScoreComponent>();
	if (score)
		score->AddToScore(amount);
}

void dae::QBertComponent::FinishLevel() const
{
	std::cout << "Congratulations!" << std::endl;
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto plates = scene->GetAllObjectsOfType<PlateComponent>();
	AwardScore(plates.size() * m_ScoreRemainingDisc);
}

void dae::QBertComponent::Move(int rowChange, int colChange)
{
	if (m_pPyramid)
	{
		bool fellOf = false;
		bool positiveChange = false;
		bool isOccupied = false;
		PlateComponent* pPlate = nullptr;
		auto* pNextCube = m_pPyramid->GetNextCube(m_pCurrentCube, rowChange, colChange, fellOf, positiveChange, isOccupied, pPlate);

		if (pPlate)
		{
			ModifyCoilyBehavior(pPlate);
			pPlate->GetGameObject()->Delete();
		}
		
		if (pNextCube) ChangeCube(pNextCube, fellOf, positiveChange, isOccupied);
	}
}

void dae::QBertComponent::ModifyCoilyBehavior(PlateComponent* pPlate)
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();

	auto pCoily = scene->GetComponentOfType<CoilyComponent>();
	if (pCoily) pCoily->SetTarget(pPlate, m_pCurrentCube);
}

void dae::QBertComponent::UpdatePosition(const glm::vec3& nextPosition)
{
	m_pObject->SetPosition(nextPosition.x, nextPosition.y);
}