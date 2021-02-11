#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "TextComponent.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text) const;
		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		void AddComponent(BaseComponent* component);

		GameObject() = default;
		explicit GameObject(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		TextComponent* m_pTextComponent = nullptr;
		std::vector<BaseComponent*> m_pComponents;
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
