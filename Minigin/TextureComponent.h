#pragma once
#include "BaseComponent.h"

namespace dae
{
    class TextureComponent : public BaseComponent
    {
    public:
        TextureComponent(const std::string& filename);
        virtual ~TextureComponent();

        void Update() override;
        void Render() const override;
    	
        TextureComponent(const TextureComponent& other) = delete;
        TextureComponent(TextureComponent&& other) = delete;
        TextureComponent& operator=(const TextureComponent& other) = delete;
        TextureComponent& operator=(TextureComponent&& other) = delete;
    private:
        std::shared_ptr<dae::Texture2D> m_pTexture;
    };
}


