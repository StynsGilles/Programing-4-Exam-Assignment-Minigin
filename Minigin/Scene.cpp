#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::RemoveDeadObjects()
{
	m_Objects.erase(std::remove_if(m_Objects.begin(),
		m_Objects.end(),
		[](std::shared_ptr<GameObject> object) {return object->GetMarkedForDeletion(); }),
		m_Objects.end());
}

std::string Scene::GetName() const
{
	return m_Name;
}

