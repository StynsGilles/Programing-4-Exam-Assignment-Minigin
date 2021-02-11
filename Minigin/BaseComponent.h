#pragma once
#include "Texture2D.h"

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();

		virtual void Update() = 0;
		virtual void Render() const = 0;
		void SetGameObject(GameObject* pObject);
		
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	protected:
		GameObject* m_pObject;
	};
}
