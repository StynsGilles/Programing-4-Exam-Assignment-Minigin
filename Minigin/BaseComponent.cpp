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

void dae::BaseComponent::Render() const
{
	if (m_pTexture)
	{
		const auto pos = m_pObject->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}
