#include "pch.h"
#include "QBertComponent.h"

#include <GameObject.h>
#include <GameTime.h>
#include <Observer.h>
#include <RenderComponent.h>
#include <Scene.h>
#include <SceneManager.h>
#include <ServiceLocator.h>
#include <SubjectComponent.h>

#include "CoilyNPCComponent.h"
#include "EntityComponent.h"
#include "LevelComponent.h"
#include "LivesComponent.h"
#include "PlateComponent.h"
#include "ScoreComponent.h"
#include "SlickAndSamComponent.h"

dae::QBertComponent::QBertComponent(LevelComponent* pPyramid, float jumpInterval, LivesComponent* pLivesComp, ScoreComponent* pScoreComp)
	: m_pPyramid(pPyramid)
	, m_pLivesComp(pLivesComp)
	, m_pScoreComp(pScoreComp)
	, m_JumpInterval(jumpInterval)
	, m_JumpCoolDown(jumpInterval)
{}

dae::QBertComponent::~QBertComponent()
{}

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
{}

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
					GotHit();
			}
		}

		if (fellOf)
		{
			m_pLivesComp->LoseLives(1);
			ServiceLocator::GetSoundSystem()->PlaySound("Data/Sounds/Fall.wav");
		}
		else
			ServiceLocator::GetSoundSystem()->PlaySound("Data/Sounds/Jump.wav");

		if (positiveChange)
			FlippedTile();

		m_pCurrentCube->entity = m_pObject;

		glm::vec3 pos = m_pCurrentCube->position;
		pos.x += m_pPyramid->GetCubeWidth() / 2.f - m_pObject->GetComponent<RenderComponent>()->GetWidth() / 2.f;
		pos.y -= m_pPyramid->GetCubeHeight() /4.f;

		UpdatePosition(pos);
	}
}

dae::LevelCube* dae::QBertComponent::GetCurrentCube() const
{
	return m_pCurrentCube;
}

void dae::QBertComponent::GotHit() const
{
	ServiceLocator::GetSoundSystem()->PlaySound("Data/Sounds/Swear.wav");
	m_pLivesComp->LoseLives(1);
}

void dae::QBertComponent::KillGreen() const
{
	AwardScore(m_ScoreSlAndSaDefeat);
	ServiceLocator::GetSoundSystem()->PlaySound("Data/Sounds/Prize.wav");
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

void dae::QBertComponent::FinishLevel() const
{	
	const auto pScene = SceneManager::GetInstance().GetCurrentScene();
	const auto pPlates = pScene->GetAllObjectsOfType<PlateComponent>();
	AwardScore(static_cast<int>(pPlates.size()) * m_ScoreRemainingDisc);
	m_pObject->GetComponent<SubjectComponent>()->Notify(m_pObject, Event::LevelFinished);
	ServiceLocator::GetSoundSystem()->PlaySound("Data/Sounds/Victory.wav");
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
			ServiceLocator::GetSoundSystem()->PlaySound("Data/Sounds/Lift.wav");
		}
		
		if (pNextCube && !otherPlayerOnCube) ChangeCube(pNextCube, fellOf, positiveChange, isOccupied);
		
		m_CanJump = false;
	}
}

void dae::QBertComponent::ModifyCoilyBehavior(PlateComponent* pPlate) const
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();

	auto pCoily = scene->GetComponentOfType<CoilyNPCComponent>();
	if (pCoily) pCoily->SetTarget(pPlate, m_pCurrentCube);
}

void dae::QBertComponent::UpdatePosition(const glm::vec3& nextPosition) const
{
	m_pObject->SetPosition(nextPosition.x, nextPosition.y);
}