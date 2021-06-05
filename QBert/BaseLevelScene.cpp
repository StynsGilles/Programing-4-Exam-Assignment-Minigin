#include "pch.h"
#include "BaseLevelScene.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"

dae::BaseLevelScene::BaseLevelScene(const std::string& name, const std::wstring& fileName)
	: Scene(name)
	, m_FileName(fileName)
{
}

void dae::BaseLevelScene::Initialize()
{
	Scene::Initialize();
	
	//Create objects
	auto go = std::make_shared<dae::GameObject>();
	auto* pBackgroundTextureComponent = new RenderComponent();
	pBackgroundTextureComponent->SetTexture("background.jpg");
	go->AddComponent(pBackgroundTextureComponent);
	Add(go);

	const auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fps = std::make_shared<GameObject>();
	auto* pTextComponent = new TextComponent("00 fps", fpsFont);
	auto* pFPSComponent = new FPSComponent(pTextComponent);
	pTextComponent->SetColor(SDL_Color{ 255, 255, 0 });
	fps->AddComponent(pTextComponent);
	fps->AddComponent(pFPSComponent);
	Add(fps);
}
