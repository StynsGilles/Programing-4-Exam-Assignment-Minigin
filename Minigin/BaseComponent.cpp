#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::BaseComponent(std::shared_ptr<GameObject> pObject)
	: m_pObject(pObject)
{
}

dae::BaseComponent::~BaseComponent()
{
}