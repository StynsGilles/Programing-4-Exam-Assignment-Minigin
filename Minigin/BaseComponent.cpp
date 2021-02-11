#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "Renderer.h"

dae::BaseComponent::BaseComponent()
{
}

dae::BaseComponent::~BaseComponent()
{
}

void dae::BaseComponent::SetGameObject(GameObject* pObject)
{
	m_pObject = pObject;
}