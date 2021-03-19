#include "MiniginPCH.h"
#include "SubjectComponent.h"
#include "Observer.h"
#include "GameObject.h"

dae::SubjectComponent::SubjectComponent()
	: BaseComponent()
{
}

dae::SubjectComponent::~SubjectComponent()
{
}

void dae::SubjectComponent::Update()
{
}

void dae::SubjectComponent::Render() const
{
}

void dae::SubjectComponent::AddObserver(Observer* observer)
{
	m_pObservers.push_back(observer);
}

void dae::SubjectComponent::RemoveObserver(Observer* observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer));
}

void dae::SubjectComponent::Notify(GameObject* object, Event event)
{
	for (Observer* o : m_pObservers)
		o->onNotify(object, event);
}
