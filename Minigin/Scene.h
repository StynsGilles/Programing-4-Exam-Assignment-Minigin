#pragma once
#include "GameObject.h"
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		//void AddAtRunTime(const std::shared_ptr<GameObject>& object);
		
		void Update();
		void Render() const;
		void RemoveDeadObjects();
		std::string	GetName() const;

		template <typename T>
		T* GetComponentOfType() const
		{
			for (auto object : m_Objects)
			{
				T* pComp = object->GetComponent<T>();
				if (pComp) return pComp;
			}
			return nullptr;
		}
		
		template <typename T>
		std::shared_ptr<GameObject> GetObjectOfType() const
		{
			for (auto object : m_Objects)
				if (object->GetComponent<T>()) return object;
			return nullptr;
		}

		template <typename T>
		std::vector<std::shared_ptr<GameObject>> GetAllObjectsOfType() const
		{
			std::vector<std::shared_ptr<GameObject>> objectsOfType;
			for (auto object : m_Objects)
				if (object->GetComponent<T>()) objectsOfType.push_back(object);

			return objectsOfType;
		}
		
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};
		//std::vector<std::shared_ptr<GameObject>> m_NewObjects{};

		static unsigned int m_IdCounter; 
	};

}
