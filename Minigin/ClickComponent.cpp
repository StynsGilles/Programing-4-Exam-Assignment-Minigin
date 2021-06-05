#include "MiniginPCH.h"
#include "ClickComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "RenderComponent.h"

dae::ClickComponent::ClickComponent(RenderComponent* pRenderComp)
	:m_pRenderComponent(pRenderComp)
{
}

dae::ClickComponent::~ClickComponent()
{
}

void dae::ClickComponent::Update()
{
	auto inputManager = SceneManager::GetInstance().GetCurrentScene()->GetInputManager();
	bool mouseClicked = inputManager->GetMouseUp();
	if (mouseClicked)
	{
		auto mousePos = inputManager->GetMousePosition();
		float TextureWidth = m_pRenderComponent->GetWidth();
		float TextureHeight = m_pRenderComponent->GetHeight();
		auto objPos = m_pObject->GetTransform().GetPosition();

		if (objPos.x <= mousePos.x && mousePos.x <= objPos.x + TextureWidth &&
			objPos.y <= mousePos.y && mousePos.y <= objPos.y + TextureHeight)
			ProcessClicked();
	}
}

void dae::ClickComponent::Render() const
{
}
