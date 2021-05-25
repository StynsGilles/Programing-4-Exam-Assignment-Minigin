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
		if (m_pCurrentCube->reversible)
		{
			switch (m_pCurrentCube->stage)
			{
			case 0:
				m_pCurrentCube->stage++;
				break;
			case 1:
				m_pCurrentCube->stage--;
				break;
			default:
				break;
			}
		}
		else
		{
			if ((size_t)m_pCurrentCube->stage + 1 < m_pCurrentCube->pCubeTextures.size())
				m_pCurrentCube->stage++;
		}
		
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
