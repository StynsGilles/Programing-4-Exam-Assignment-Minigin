#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "TextComponent.h"
#include "GameObject.h"

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, std::shared_ptr<GameObject> pObject)
	: BaseComponent(pObject)
	, m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(font)
{
}

dae::TextComponent::~TextComponent()
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
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
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_pObject->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}