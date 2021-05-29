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

dae::Scene& dae::SceneManager::GetCurrentScene() const
{
	return *m_ActiveScene.lock();
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
	int indexCurScene = -1;
	if (std::shared_ptr<Scene> pSharedActiveScene = m_ActiveScene.lock())
	{
		for (size_t idx = 0; idx < m_Scenes.size(); ++idx)
		{
			if (pSharedActiveScene == m_Scenes[idx])
			{
				indexCurScene = idx;
			}
		}
	}

	const int indexPrevScene = indexCurScene - 1;
	
	if (0 <= indexPrevScene && indexPrevScene < (int)m_Scenes.size())
	{
		m_ActiveScene = m_Scenes[indexPrevScene];
	}
}

void dae::SceneManager::NextScene()
{
	int indexCurScene = -1;
	if (std::shared_ptr<Scene> pSharedActiveScene = m_ActiveScene.lock())
	{
		for (size_t idx = 0; idx < m_Scenes.size(); ++idx)
		{
			if (pSharedActiveScene == m_Scenes[idx])
			{
				indexCurScene = idx;
			}
		}
	}

	const int indexPrevScene = indexCurScene + 1;

	if (0 <= indexPrevScene && indexPrevScene < (int)m_Scenes.size())
	{
		m_ActiveScene = m_Scenes[indexPrevScene];
	}
}
