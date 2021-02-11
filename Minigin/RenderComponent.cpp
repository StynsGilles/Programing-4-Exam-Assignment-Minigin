#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::RenderComponent::RenderComponent()
	: m_pTexture(nullptr)
{}

dae::RenderComponent::RenderComponent(const std::string& filename)
{
	SetTexture(filename);
}

dae::RenderComponent::~RenderComponent()
{
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render() const
{
	if (m_pTexture)
	{
		const auto pos = m_pObject->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_pTexture = texture;
}
