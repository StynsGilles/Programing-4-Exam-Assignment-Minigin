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
	switch (m_Side)
	{
	case Side::left:
	{
		auto* pCube = m_pPyramid->GetCube(m_Row, 0);
		auto pPlatePos = pCube->position;
		pPlatePos.x -= (m_pObject->GetComponent<RenderComponent>()->GetWidth() + 1);
		pPlatePos.y += 10.f;
		m_pObject->SetPosition(pPlatePos.x, pPlatePos.y);
	}
	break;
	case Side::right:
	{
		auto* pCube = m_pPyramid->GetCube(m_Row, m_Row);
		auto pPlatePos = pCube->position;
		SDL_Rect dst;
		SDL_QueryTexture(pCube->pCubeTextures[pCube->stage]->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
		pPlatePos.x += dst.w + 1;
		pPlatePos.y += 10.f;
		m_pObject->SetPosition(pPlatePos.x, pPlatePos.y);
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
