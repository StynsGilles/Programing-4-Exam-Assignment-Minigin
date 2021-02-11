#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "Renderer.h"

dae::BaseComponent::BaseComponent(std::shared_ptr<GameObject> pObject)
	: m_pObject(pObject.get())
{
}

dae::BaseComponent::~BaseComponent()
{
}
