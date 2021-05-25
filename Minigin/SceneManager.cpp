#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	if (std::shared_ptr<Scene> pSharedActiveScene = m_ActiveScene.lock())
		pSharedActiveScene->Update();
}

void dae::SceneManager::Render()
{
	if (std::shared_ptr<Scene> pSharedActiveScene = m_ActiveScene.lock())
		pSharedActiveScene->Render();
}

void dae::SceneManager::RemoveDeadObjects()
{
	if (std::shared_ptr<Scene> pSharedActiveScene = m_ActiveScene.lock())
		pSharedActiveScene->RemoveDeadObjects();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	if (m_ActiveScene.expired())
		m_ActiveScene = scene;
	return *scene;
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	for (auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			m_ActiveScene = scene;
			return;
		}
	}
	std::cout << "SceneManager::SetActiveScene: scene with name " << name << " not found!" << std::endl;
}

void dae::SceneManager::PreviousScene()
{
	size_t indexCurScene = -1;
	if (std::shared_ptr<Scene> pSharedActiveScene = m_ActiveScene.lock())
	{
		for (size_t idx; idx < m_Scenes.size(); ++idx)
		{
			if (pSharedActiveScene == m_Scenes[idx])
			{
				indexCurScene = idx;
			}
		}
	}

	size_t indexPrevScene = indexCurScene - 1;
	
	if (0 <= indexPrevScene && indexPrevScene < m_Scenes.size())
	{
		m_ActiveScene = m_Scenes[indexPrevScene];
	}
}

void dae::SceneManager::NextScene()
{
	size_t indexCurScene = -1;
	if (std::shared_ptr<Scene> pSharedActiveScene = m_ActiveScene.lock())
	{
		for (size_t idx; idx < m_Scenes.size(); ++idx)
		{
			if (pSharedActiveScene == m_Scenes[idx])
			{
				indexCurScene = idx;
			}
		}
	}

	size_t indexPrevScene = indexCurScene + 1;

	if (0 <= indexPrevScene && indexPrevScene < m_Scenes.size())
	{
		m_ActiveScene = m_Scenes[indexPrevScene];
	}
}
