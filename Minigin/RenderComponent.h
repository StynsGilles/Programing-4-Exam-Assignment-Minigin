#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class RenderComponent final : public BaseComponent
    {
    public:
        explicit RenderComponent();
        explicit RenderComponent(const std::string& filename);
        virtual ~RenderComponent();

        void Update() override;
        void Render() const override;
        void SetTexture(const std::string& filename);
        void SetTexture(std::shared_ptr<Texture2D> texture);
        std::shared_ptr<Texture2D> GetTexture() const;
        void SetDimensions(float width, float height);
        float GetWidth() const;
        float GetHeight() const;
    	
        RenderComponent(const RenderComponent& other) = delete;
        RenderComponent(RenderComponent&& other) = delete;
        RenderComponent& operator=(const RenderComponent& other) = delete;
        RenderComponent& operator=(RenderComponent&& other) = delete;
    private:
        std::shared_ptr<Texture2D> m_pTexture;
        float m_Width, m_Height;
        bool m_DimensionsSet = false;
    };
}