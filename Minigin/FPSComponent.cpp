#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "FPSComponent.h"
#include "Time.h"

dae::FPSComponent::FPSComponent(const std::shared_ptr<Font>& font, std::shared_ptr<GameObject> pObject)
	: BaseComponent(pObject)
	, m_Font(font)
{
}

dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::Update()
{
	auto& time = Time::GetInstance();
	const auto fps = time.GetFPS();
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), std::to_string(fps).c_str(), color);
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
}

void dae::FPSComponent::Render() const
{
	BaseComponent::Render();
}
