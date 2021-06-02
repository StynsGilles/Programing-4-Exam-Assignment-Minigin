#pragma once
#include "Transform.h"
#include "BaseComponent.h"
#include <vector>

namespace dae
{
	class GameObject final
	{
	public:
		void Update();
		void Render() const;
		
		void SetPosition(float x, float y);
		Transform GetTransform() const;
		void AddComponent(BaseComponent* component);
		bool GetMarkedForDeletion() const;
		void Delete();
		template <typename T>
		T* GetComponent() const
		{
			for (BaseComponent* component : m_pComponents)
				if (dynamic_cast<T*>(component)) return (T*)component;
			return nullptr;
		}
		void RemoveComponent(BaseComponent* pComponent);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		bool m_MarkedForDeletion = false;
		std::vector<BaseComponent*> m_pComponents{};
		Transform m_Transform;
	};
}
