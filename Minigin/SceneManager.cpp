#include "MiniginPCH.h"
#include "SceneManager.h"

#include "Scene.h"

void dae::SceneManager::Update()
{
	m_ActiveScene->Update();
}

void dae::SceneManager::Render() const
{
	m_ActiveScene->Render();
}

void dae::SceneManager::RemoveDeadObjects() const
{
	m_ActiveScene->RemoveDeadObjects();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::make_shared<Scene>(name);
	m_Scenes.push_back(scene);
	if (!m_ActiveScene)
		m_ActiveScene = scene;
	return *scene;
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_Scenes.push_back(scene);
	if (!m_ActiveScene)
		m_ActiveScene = scene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetCurrentScene() const
{
	return m_ActiveScene;
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	for (auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			m_ActiveScene = scene;
			m_ActiveScene->ResetScene();
			return;
		}
	}
	std::cout << "SceneManager::SetActiveScene: scene with name " << name << " not found!" << std::endl;
}

void dae::SceneManager::PreviousScene()
{
	int indexCurScene = -1;
	if (const std::shared_ptr<Scene> pSharedActiveScene = m_ActiveScene)
	{
		for (size_t idx = 0; idx < m_Scenes.size(); ++idx)
		{
			if (pSharedActiveScene == m_Scenes[idx])
				indexCurScene = static_cast<int>(idx);
		}
	}

	const int indexPrevScene = indexCurScene - 1;
	
	if (0 <= indexPrevScene && indexPrevScene < static_cast<int>(m_Scenes.size()))
	{
		m_ActiveScene = m_Scenes[indexPrevScene];
		m_ActiveScene->ResetScene();
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::NextScene()
{
	int indexCurScene = -1;
	if (const std::shared_ptr<Scene> pSharedActiveScene = m_ActiveScene)
	{
		for (size_t idx = 0; idx < m_Scenes.size(); ++idx)
		{
			if (pSharedActiveScene == m_Scenes[idx])
				indexCurScene = static_cast<int>(idx);
		}
	}

	const int indexPrevScene = indexCurScene + 1;

	if (0 <= indexPrevScene && indexPrevScene < static_cast<int>(m_Scenes.size()))
	{
		m_ActiveScene = m_Scenes[indexPrevScene];
		m_ActiveScene->ResetScene();
		return m_ActiveScene;
	}
	
	return nullptr;
}
