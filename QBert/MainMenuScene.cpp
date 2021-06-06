#include "pch.h"
#include "MainMenuScene.h"

#include <TextComponent.h>

#include "MenuClickComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"

dae::MainMenuScene::MainMenuScene(const std::string& name)
	: Scene(name)
{}

dae::MainMenuScene::~MainMenuScene()
{}

void dae::MainMenuScene::Initialize()
{
	Scene::Initialize();

	const auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	
	auto pBackground = std::make_shared<GameObject>();
	auto* pBackgroundTextureComponent = new RenderComponent();
	pBackgroundTextureComponent->SetTexture("background.jpg");
	pBackgroundTextureComponent->SetDimensions(640, 480);
	pBackground->AddComponent(pBackgroundTextureComponent);
	Add(pBackground);
	
	const float x = 188.f;
	float y = 108;
	const float textOffsetX = 50.f;
	const float textOffsetY = 20.f;
	
	auto pButtonSinglePlayer = std::make_shared<GameObject>();
	auto* pSingleTextureComponent = new RenderComponent();
	auto* pSingleTextComponent = new TextComponent("SinglePlayer", pFont, textOffsetX, textOffsetY);
	auto* pSingleClickComp = new MenuClickComponent(pSingleTextureComponent, "Level1");
	pSingleTextureComponent->SetTexture("Button.png");
	pButtonSinglePlayer->AddComponent(pSingleTextureComponent);
	pButtonSinglePlayer->AddComponent(pSingleTextComponent);
	pButtonSinglePlayer->AddComponent(pSingleClickComp);
	pButtonSinglePlayer->SetPosition(x, y);
	Add(pButtonSinglePlayer);

	y += 88.f;
	
	auto pButtonVersus = std::make_shared<GameObject>();
	auto* pVersusTextureComponent = new RenderComponent();
	auto* pVersusTextComponent = new TextComponent("Versus", pFont, textOffsetX, textOffsetY);
	auto* pVersusClickComp = new MenuClickComponent(pVersusTextureComponent, "VersusLevel1");
	pVersusTextureComponent->SetTexture("Button.png");
	pButtonVersus->AddComponent(pVersusTextureComponent);
	pButtonVersus->AddComponent(pVersusTextComponent);
	pButtonVersus->AddComponent(pVersusClickComp);
	pButtonVersus->SetPosition(x, y);
	Add(pButtonVersus);

	y += 88.f;
	
	auto pButtonCoop = std::make_shared<GameObject>();
	auto* pCoopTextureComponent = new RenderComponent();
	auto* pCoopTextComponent = new TextComponent("Coop", pFont, textOffsetX, textOffsetY);
	auto* pCoopClickComp = new MenuClickComponent(pCoopTextureComponent, "CoopLevel1");
	pCoopTextureComponent->SetTexture("Button.png");
	pButtonCoop->AddComponent(pCoopTextureComponent);
	pButtonCoop->AddComponent(pCoopTextComponent);
	pButtonCoop->AddComponent(pCoopClickComp);
	pButtonCoop->SetPosition(x, y);
	Add(pButtonCoop);
}
