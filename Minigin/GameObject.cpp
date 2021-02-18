#include "MiniginPCH.h"
#include "GameObject.h"

dae::GameObject::~GameObject()
{
	for (BaseComponent* component : m_pComponents)
	{
		delete component;
	}
};

void dae::GameObject::Update()
{
	for (BaseComponent* component : m_pComponents)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for (BaseComponent* component : m_pComponents)
	{
		component->Render();
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
	m_MarkedForDeletion = true;
}
