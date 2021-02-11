#pragma once
#include "BaseComponent.h"
#include "Font.h"

namespace dae
{
    class GameObject;
    class TextComponent final : public BaseComponent
    {
    public:
        explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font, std::shared_ptr<GameObject> pObject);
        virtual ~TextComponent();

        void Update() override;
        void Render() const override;
        void SetText(const std::string& text);

        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;
    private:
        bool m_NeedsUpdate;
        std::string m_Text;
        std::shared_ptr<Font> m_Font;
    };
}