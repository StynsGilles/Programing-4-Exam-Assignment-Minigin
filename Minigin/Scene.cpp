#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name(name)
	, m_InputManager(new InputManager())
{
	
}

Scene::~Scene()
{
	delete m_InputManager;
}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for (size_t idx = 0; idx < m_Objects.size(); ++idx)
		m_Objects[idx]->Update();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
		object->Render();
}

void Scene::Initialize()
{
}

void Scene::InitializeInputs()
{
}

void Scene::ResetScene()
{
	m_Objects.clear();
	m_InputManager->ClearInputs();
	Initialize();
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

InputManager* Scene::GetInputManager() const
{
	return m_InputManager;
}
