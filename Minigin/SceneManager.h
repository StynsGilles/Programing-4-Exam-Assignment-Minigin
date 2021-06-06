#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void AddScene(std::shared_ptr<Scene> scene);
		std::shared_ptr<dae::Scene> GetCurrentScene() const;
		void SetActiveScene(const std::string& name);
		void PreviousScene();
		std::shared_ptr<Scene> NextScene();
		
		void Update();
		void Render();
		void RemoveDeadObjects();
	
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
	};
}
