#pragma once
#include "Texture2D.h"

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(std::shared_ptr<GameObject> pObject);
		virtual ~BaseComponent();

		virtual void Update() = 0;
		virtual void Render() const;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	protected:
		GameObject* m_pObject;
		std::shared_ptr<dae::Texture2D> m_pTexture;
	};
}
