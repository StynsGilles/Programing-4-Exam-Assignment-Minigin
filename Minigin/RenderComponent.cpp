#include "MiniginPCH.h"
#include "RenderComponent.h"

#include <SDL_render.h>

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
		if (m_DimensionsSet)
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Width, m_Height);
		else
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	if(!m_DimensionsSet)
	{
		SDL_Rect dst;
		SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
		m_Width = static_cast<float>(dst.w);
		m_Height = static_cast<float>(dst.h);
	}
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_pTexture = texture;
}

std::shared_ptr<dae::Texture2D> dae::RenderComponent::GetTexture() const
{
	return m_pTexture;
}

void dae::RenderComponent::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
	m_DimensionsSet = true;
}

float dae::RenderComponent::GetWidth() const
{
	return m_Width;
}

float dae::RenderComponent::GetHeight() const
{
	return m_Height;
}
