#include "MiniginPCH.h"
#include "BaseComponent.h"

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

dae::GameObject* dae::BaseComponent::GetGameObject() const
{
	return m_pObject;
}
