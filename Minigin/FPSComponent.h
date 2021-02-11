#pragma once
#include "BaseComponent.h"
#include "Font.h"

namespace dae
{
	class GameObject;
	class FPSComponent : public BaseComponent
	{
    public:
        explicit FPSComponent(const std::shared_ptr<Font>& font, std::shared_ptr<GameObject> pObject);
        virtual ~FPSComponent();

        void Update() override;
        void Render() const override;
		
        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;
    private:
        std::shared_ptr<Font> m_Font;
        std::shared_ptr<dae::Texture2D> m_pTexture;
    };
}