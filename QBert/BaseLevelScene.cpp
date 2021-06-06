#include "pch.h"
#include "BaseLevelScene.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"

dae::BaseLevelScene::BaseLevelScene(const std::string& name, int level)
	: Scene(name)
	, m_Level(level)
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

int dae::BaseLevelScene::GetLevel() const
{
	return m_Level;
}

int dae::BaseLevelScene::GetMaxLevel()
{
	return m_MaxLevel;
}

bool dae::BaseLevelScene::IsLastLevel() const
{
	return m_Level == m_MaxLevel;
}
