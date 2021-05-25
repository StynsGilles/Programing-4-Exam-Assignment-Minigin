#include "QBertComponent.h"

#include <SDL_render.h>

#include "GameObject.h"

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

void dae::QBertComponent::ChangeCube(LevelCube* pNewCube)
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
}

dae::LevelCube* dae::QBertComponent::GetCurrentCube() const
{
	return m_pCurrentCube;
}

void dae::QBertComponent::UpdatePosition(const glm::vec3& nextPosition)
{
	m_pObject->SetPosition(nextPosition.x, nextPosition.y);
}
