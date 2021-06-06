#include "MiniginPCH.h"
#include "FPSComponent.h"

#include "GameTime.h"
#include "TextComponent.h"

dae::FPSComponent::FPSComponent(TextComponent* pTextComponent)
	: m_pTextComponent(pTextComponent)
{}

dae::FPSComponent::~FPSComponent()
{}

void dae::FPSComponent::Update()
{
	m_TimeSinceLastUpdate += GameTime::GetInstance().GetDeltaTime();

	if (m_TimeSinceLastUpdate >= m_UpdateFPSInterval)
	{
		if (m_pTextComponent) m_pTextComponent->SetText(std::to_string(GameTime::GetInstance().GetFPS()) + " FPS");
		m_TimeSinceLastUpdate -= m_UpdateFPSInterval;
	}
}

void dae::FPSComponent::Render() const
{}