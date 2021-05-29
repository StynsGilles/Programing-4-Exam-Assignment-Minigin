#include "pch.h"
#include "SlickAndSamComponent.h"
#include <SDL_render.h>
#include <GameTime.h>
#include "GameObject.h"
#include "LevelComponent.h"

dae::SlickAndSamComponent::SlickAndSamComponent(LevelComponent* pPyramid)
	: m_pPyramid(pPyramid)
{
}

dae::SlickAndSamComponent::~SlickAndSamComponent()
{
}

void dae::SlickAndSamComponent::Update()
{
	const float jumpInterval = 2.f;
	m_JumpTimer += GameTime::GetInstance().GetDeltaTime();

	if(m_JumpTimer>= jumpInterval)
	{
		Jump();
		m_JumpTimer -= jumpInterval;
	}
}

void dae::SlickAndSamComponent::Jump()
{
	int randomNumber = rand() % 2;

	LevelCube* pNextCube = nullptr;

	switch (randomNumber)
	{
	case 0:
		pNextCube = m_pPyramid->GetNextCubeEnemy(m_pCurrentCube, 1, 0, true);
		break;
	case 1:
		pNextCube = m_pPyramid->GetNextCubeEnemy(m_pCurrentCube, 1, 1, true);
		break;
	default:
		break;
	}

	ChangeCube(pNextCube);
}

void dae::SlickAndSamComponent::Render() const
{
}

void dae::SlickAndSamComponent::ChangeCube(LevelCube* pNewCube)
{
	m_pCurrentCube = pNewCube;
	if (m_pCurrentCube)
	{
		SDL_Rect dst;
		SDL_QueryTexture(pNewCube->pCubeTextures[pNewCube->stage]->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

		glm::vec3 pos = m_pCurrentCube->position;
		pos.x += (float)dst.w / 3.f;
		pos.y -= 5.f;

		UpdatePosition(pos);
	}
	else
		m_pObject->Delete();
}

dae::LevelCube* dae::SlickAndSamComponent::GetCurrentCube() const
{
	return m_pCurrentCube;
}

void dae::SlickAndSamComponent::UpdatePosition(const glm::vec3& nextPosition)
{
	m_pObject->SetPosition(nextPosition.x, nextPosition.y);
}
