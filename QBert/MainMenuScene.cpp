#include "pch.h"
#include "MainMenuScene.h"

#include "ClickComponent.h"
#include "MenuClickComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"

dae::MainMenuScene::MainMenuScene(const std::string& name)
	: Scene(name)
{
}

void dae::MainMenuScene::Initialize()
{
	Scene::Initialize();

	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	
	auto go = std::make_shared<GameObject>();
	auto* pBackgroundTextureComponent = new RenderComponent();
	pBackgroundTextureComponent->SetTexture("background.jpg");
	go->AddComponent(pBackgroundTextureComponent);
	Add(go);
	
	float x = 188.f;
	float y = 108;
	float textOffsetX = 50.f;
	float textOffsetY = 20.f;

	
	auto buttonSinglePlayer = std::make_shared<GameObject>();
	auto* pSingleTextureComponent = new RenderComponent();
	auto* pSingleTextComponent = new TextComponent("SinglePlayer", font, textOffsetX, textOffsetY);
	auto* pSingleClickComp = new MenuClickComponent(pSingleTextureComponent);
	pSingleTextureComponent->SetTexture("Button.png");
	buttonSinglePlayer->AddComponent(pSingleTextureComponent);
	buttonSinglePlayer->AddComponent(pSingleTextComponent);
	buttonSinglePlayer->AddComponent(pSingleClickComp);
	buttonSinglePlayer->SetPosition(x, y);
	Add(buttonSinglePlayer);

	y += 88.f;
	
	auto buttonVersus = std::make_shared<GameObject>();
	auto* pVersusTextureComponent = new RenderComponent();
	auto* pVersusTextComponent = new TextComponent("Versus", font, textOffsetX, textOffsetY);
	auto* pVersusClickComp = new MenuClickComponent(pVersusTextureComponent);
	pVersusTextureComponent->SetTexture("Button.png");
	buttonVersus->AddComponent(pVersusTextureComponent);
	buttonVersus->AddComponent(pVersusTextComponent);
	buttonVersus->AddComponent(pVersusClickComp);
	buttonVersus->SetPosition(x, y);
	Add(buttonVersus);

	y += 88.f;
	
	auto buttonCoop = std::make_shared<GameObject>();
	auto* pCoopTextureComponent = new RenderComponent();
	auto* pCoopTextComponent = new TextComponent("Coop", font, textOffsetX, textOffsetY);
	auto* pCoopClickComp = new MenuClickComponent(pCoopTextureComponent);
	pCoopTextureComponent->SetTexture("Button.png");
	buttonCoop->AddComponent(pCoopTextureComponent);
	buttonCoop->AddComponent(pCoopTextComponent);
	buttonCoop->AddComponent(pCoopClickComp);
	buttonCoop->SetPosition(x, y);
	Add(buttonCoop);
}
