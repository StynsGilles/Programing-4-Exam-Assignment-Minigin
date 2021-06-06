#include "pch.h"
#include "PlateComponent.h"

#include <SDL_render.h>


#include "GameObject.h"
#include "LevelComponent.h"
#include "RenderComponent.h"

dae::PlateComponent::PlateComponent(LevelComponent* pPyramid, int row, Side side)
	: m_pPyramid(pPyramid)
	, m_Side(side)
	, m_Row(row)
{}

dae::PlateComponent::~PlateComponent()
{}

void dae::PlateComponent::Initialize()
{
	const float yOffset = 22.f;
	const float xOffset = 3.f;
	
	switch (m_Side)
	{
	case Side::left:
	{
		auto* pCube = m_pPyramid->GetCube(m_Row, 0);
		if (pCube)
		{
			auto pPlatePos = pCube->position;
			pPlatePos.x -= m_pObject->GetComponent<RenderComponent>()->GetWidth() + xOffset;
			pPlatePos.y += yOffset;
			m_pObject->SetPosition(pPlatePos.x, pPlatePos.y);
		}

	}
	break;
	case Side::right:
	{
		auto* pCube = m_pPyramid->GetCube(m_Row, m_Row);
		if (pCube)
		{
			auto pPlatePos = pCube->position;
			pPlatePos.x += m_pPyramid->GetCubeWidth() + xOffset;
			pPlatePos.y += yOffset;
			m_pObject->SetPosition(pPlatePos.x, pPlatePos.y);
		}
	}
		break;
	default:
		break;
	}
}

void dae::PlateComponent::Update()
{
}

void dae::PlateComponent::Render() const
{
}

int dae::PlateComponent::GetRow() const
{
	return m_Row;
}

dae::Side dae::PlateComponent::GetSide() const
{
	return m_Side;
}
