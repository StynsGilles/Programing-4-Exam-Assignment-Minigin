#pragma once
#include "BaseComponent.h"

namespace dae
{
    class RenderComponent : public BaseComponent
    {
    public:
        RenderComponent();
        RenderComponent(const std::string& filename);
        virtual ~RenderComponent();

        void Update() override;
        void Render() const override;
        void SetTexture(const std::string& filename);
        void SetTexture(std::shared_ptr<Texture2D> texture);
    	
        RenderComponent(const RenderComponent& other) = delete;
        RenderComponent(RenderComponent&& other) = delete;
        RenderComponent& operator=(const RenderComponent& other) = delete;
        RenderComponent& operator=(RenderComponent&& other) = delete;
    private:
        std::shared_ptr<Texture2D> m_pTexture;
    };
}