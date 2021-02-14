#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "Time.h"
#include "TextComponent.h"

dae::FPSComponent::FPSComponent(TextComponent* pTextComponent)
	: m_pTextComponent(pTextComponent)
{
}

dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::Update()
{
	if (m_pTextComponent) m_pTextComponent->SetText(std::to_string(Time::GetInstance().GetFPS()) + " FPS");
}

void dae::FPSComponent::Render() const
{
}