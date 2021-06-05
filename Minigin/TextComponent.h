#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include <SDL.h>

namespace dae
{
    class Texture2D;
	
	class TextComponent final : public BaseComponent
    {
    public:
        explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
        virtual ~TextComponent();

        void Update() override;
        void Render() const override;
        void SetText(const std::string& text);
        void SetColor(const SDL_Color& color);

        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;
    private:
        bool m_NeedsUpdate;
        std::string m_Text;
        std::shared_ptr<Font> m_Font;
        SDL_Color m_Color;
        std::shared_ptr<Texture2D> m_pTexture;
    };
}