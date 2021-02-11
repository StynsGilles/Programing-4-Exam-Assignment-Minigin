#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject(const std::string& text, const std::shared_ptr<Font>& font)
	: m_pTextComponent{ new TextComponent(text, font) }
{
}

dae::GameObject::~GameObject()
{
	delete m_pTextComponent;
};

void dae::GameObject::Update()
{
	if (m_pTextComponent)
	{
		m_pTextComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	if (m_Texture)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
	if (m_pTextComponent)
	{
		m_pTextComponent->Render();
	}
}

void dae::GameObject::SetText(const std::string& text) const
{
	if (m_pTextComponent)
	{
		m_pTextComponent->SetText(text);
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
	if (m_pTextComponent)
	{
		m_pTextComponent->SetPosition(x, y);
	}
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	m_pComponents.push_back(component);
}
