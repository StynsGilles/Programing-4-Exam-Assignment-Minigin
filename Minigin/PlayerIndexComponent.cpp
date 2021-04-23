#include <MiniginPCH.h>
#include "PlayerIndexComponent.h"

dae::PlayerIndexComponent::PlayerIndexComponent(int index)
	: BaseComponent()
	, m_PlayerIndex(index)
{
}

dae::PlayerIndexComponent::~PlayerIndexComponent()
{
}

void dae::PlayerIndexComponent::Update()
{
}

void dae::PlayerIndexComponent::Render() const
{
}

int dae::PlayerIndexComponent::GetIndex() const
{
	return m_PlayerIndex;
}
