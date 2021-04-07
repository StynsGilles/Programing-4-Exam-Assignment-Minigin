#include "MiniginPCH.h"
#include "GameObject.h"

void dae::GameObject::RemoveComponent(BaseComponent* pComponent)
{
	m_pComponents.erase(std::remove_if(m_pComponents.begin(),
		m_pComponents.end(),
		[pComponent](BaseComponent* pObjectComponent) {return pObjectComponent == pComponent; }),
		m_pComponents.end());
	delete pComponent;
}

dae::GameObject::~GameObject()
{
	for (BaseComponent* pComponent : m_pComponents)
	{
		delete pComponent;
	}
};

void dae::GameObject::Update()
{
	for (BaseComponent* pComponent : m_pComponents)
	{
		pComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	for (BaseComponent* pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

dae::Transform dae::GameObject::GetTransform() const
{
	return m_Transform;
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	component->SetGameObject(this);
	m_pComponents.push_back(component);
}

bool dae::GameObject::GetMarkedForDeletion() const
{
	return m_MarkedForDeletion;
}

void dae::GameObject::Delete()
{
	std::cout << "Killing object" << std::endl;
	m_MarkedForDeletion = true;
}
