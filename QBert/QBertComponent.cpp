#include "pch.h"
#include "QBertComponent.h"
#include <SDL_render.h>

#include "CoilyNPCComponent.h"
#include "EntityComponent.h"
#include "GameObject.h"
#include "GameTime.h"
#include "LivesComponent.h"
#include "Observer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ScoreComponent.h"
#include "SlickAndSamComponent.h"
#include "SubjectComponent.h"

dae::QBertComponent::QBertComponent(LevelComponent* pPyramid, float jumpInterval, LivesComponent* pLivesComp, ScoreComponent* pScoreComp)
	: m_pPyramid(pPyramid)
	, m_JumpInterval(jumpInterval)
	, m_pLivesComp(pLivesComp)
	, m_pScoreComp(pScoreComp)
{
}

dae::QBertComponent::~QBertComponent()
{
}

void dae::QBertComponent::Update()
{
	if (!m_CanJump)
	{
		m_JumpCoolDown -= GameTime::GetInstance().GetDeltaTime();
		if (m_JumpCoolDown <= 0.f)
		{
			m_CanJump = true;
			m_JumpCoolDown = m_JumpInterval;
		}
	}
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
					m_pLivesComp->LoseLives(1);
			}
		}

		if (fellOf)
			m_pLivesComp->LoseLives(1);

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

void dae::QBertComponent::GotHit() const
{
	m_pLivesComp->LoseLives(1);
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
	if (m_pScoreComp)
		m_pScoreComp->AddToScore(amount);
}

void dae::QBertComponent::FinishLevel()
{	
	std::cout << "Congratulations!" << std::endl;
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto plates = scene->GetAllObjectsOfType<PlateComponent>();
	AwardScore(plates.size() * m_ScoreRemainingDisc);
	m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::LevelFinished);
}

void dae::QBertComponent::Move(int rowChange, int colChange)
{
	if (!m_CanJump)
		return;
	
	if (m_pPyramid)
	{
		bool fellOf = false;
		bool positiveChange = false;
		bool isOccupied = false;
		bool otherPlayerOnCube = false;
		PlateComponent* pPlate = nullptr;
		auto* pNextCube = m_pPyramid->GetNextCube(m_pCurrentCube, rowChange, colChange, fellOf, positiveChange, isOccupied, otherPlayerOnCube, pPlate);

		if (pPlate)
		{
			ModifyCoilyBehavior(pPlate);
			pPlate->GetGameObject()->Delete();
		}
		
		if (pNextCube && !otherPlayerOnCube) ChangeCube(pNextCube, fellOf, positiveChange, isOccupied);
		
		m_CanJump = false;
	}
}

void dae::QBertComponent::ModifyCoilyBehavior(PlateComponent* pPlate)
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();

	auto pCoily = scene->GetComponentOfType<CoilyNPCComponent>();
	if (pCoily) pCoily->SetTarget(pPlate, m_pCurrentCube);
}

void dae::QBertComponent::UpdatePosition(const glm::vec3& nextPosition)
{
	m_pObject->SetPosition(nextPosition.x, nextPosition.y);
}