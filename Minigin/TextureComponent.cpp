#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename, std::shared_ptr<GameObject> pObject)
	: BaseComponent(pObject)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

dae::TextureComponent::~TextureComponent()
{
}

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::Render() const
{
	BaseComponent::Render();
	//if (m_pTexture)
	//{
	//	const auto pos = m_pObject->GetTransform().GetPosition();
	//	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	//}
}
