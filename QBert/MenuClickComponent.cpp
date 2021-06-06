#include "pch.h"
#include "MenuClickComponent.h"
#include <SceneManager.h>

dae::MenuClickComponent::MenuClickComponent(RenderComponent* pRenderComp, const std::string& sceneName)
	: ClickComponent(pRenderComp)
	, m_SceneName(sceneName)
{
}

dae::MenuClickComponent::~MenuClickComponent()
{
}

void dae::MenuClickComponent::ProcessClicked()
{
	SceneManager::GetInstance().SetActiveScene(m_SceneName);
}
