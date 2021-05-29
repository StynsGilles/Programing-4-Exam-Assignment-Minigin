#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetCurrentScene() const;
		void SetActiveScene(const std::string& name);
		void PreviousScene();
		void NextScene();
		
		void Update();
		void Render();
		void RemoveDeadObjects();
	
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::weak_ptr<Scene> m_ActiveScene;
	};
}
