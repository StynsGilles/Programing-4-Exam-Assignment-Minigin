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

//void dae::Scene::AddAtRunTime(const std::shared_ptr<GameObject>& object)
//{
//	m_NewObjects.push_back(object);
//}

void Scene::Update()
{
	for (size_t idx = 0; idx < m_Objects.size(); ++idx)
		m_Objects[idx]->Update();

	//if (m_NewObjects.size() > 0)
	//{
	//	for (size_t idx = 0; idx < m_NewObjects.size(); ++idx)
	//		m_Objects.push_back(m_NewObjects[idx]);

	//	m_NewObjects.clear();
	//}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
		object->Render();
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

