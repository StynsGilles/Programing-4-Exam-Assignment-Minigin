#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"

namespace dae
{
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;
		
		void SetPosition(float x, float y);
		Transform GetTransform() const;
		void AddComponent(BaseComponent* component);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<BaseComponent*> m_pComponents;
		Transform m_Transform;
	};
}
