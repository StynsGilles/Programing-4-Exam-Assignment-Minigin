#include "MiniginPCH.h"
#include "ClickComponent.h"

#include "RenderComponent.h"
#include "Scene.h"
#include "SceneManager.h"

dae::ClickComponent::ClickComponent(RenderComponent* pRenderComp)
	:m_pRenderComponent(pRenderComp)
{
}

dae::ClickComponent::~ClickComponent()
{
}

void dae::ClickComponent::Update()
{
	const auto inputManager = SceneManager::GetInstance().GetCurrentScene()->GetInputManager();
	const bool mouseClicked = inputManager->GetMouseUp();
	if (mouseClicked)
	{
		const auto mousePos = inputManager->GetMousePosition();
		const float TextureWidth = m_pRenderComponent->GetWidth();
		const float TextureHeight = m_pRenderComponent->GetHeight();
		const auto objPos = m_pObject->GetTransform().GetPosition();

		if (objPos.x <= mousePos.x && mousePos.x <= objPos.x + TextureWidth &&
			objPos.y <= mousePos.y && mousePos.y <= objPos.y + TextureHeight)
			ProcessClicked();
	}
}

void dae::ClickComponent::Render() const
{
}
