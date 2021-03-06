#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
	class FPSComponent final : public BaseComponent
	{
    public:
        explicit FPSComponent(TextComponent* pTextComponent);
        ~FPSComponent();

        void Update() override;
        void Render() const override;
		
        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;
    private:
        TextComponent* m_pTextComponent;
        const float m_UpdateFPSInterval = 0.3f;
        float m_TimeSinceLastUpdate = 0.f;
    };
}