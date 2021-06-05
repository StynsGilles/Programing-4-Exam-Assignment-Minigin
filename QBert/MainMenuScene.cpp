#include "pch.h"
#include "MainMenuScene.h"

#include "RenderComponent.h"

dae::MainMenuScene::MainMenuScene(const std::string& name)
	: Scene(name)
{
}

void dae::MainMenuScene::Initialize()
{
	Scene::Initialize();
	
	auto button = std::make_shared<dae::GameObject>();
	auto* pLogoTextureComponent = new RenderComponent();
	pLogoTextureComponent->SetTexture("Button.png");
	button->AddComponent(pLogoTextureComponent);
	button->SetPosition(216, 180);
	Add(button);
}
