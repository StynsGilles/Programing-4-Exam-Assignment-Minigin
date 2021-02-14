#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "TextComponent.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, RenderComponent* pTextureComponent)
	: m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(font)
	, m_pTextureComponent(pTextureComponent)
	, m_Color(SDL_Color{ 255, 255, 255 })
{
}

dae::TextComponent::~TextComponent()
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		if (m_pTextureComponent)
		{
			m_pTextureComponent->SetTexture(std::make_shared<Texture2D>(texture));
		}
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}
