#pragma once
#include <BaseComponent.h>

namespace dae
{
    class PlayerIndexComponent final : public BaseComponent
    {
    public:
        explicit PlayerIndexComponent(int index);
        virtual ~PlayerIndexComponent();

        void Update() override;
        void Render() const override;
        int GetIndex() const;
    	
        PlayerIndexComponent(const PlayerIndexComponent& other) = delete;
        PlayerIndexComponent(PlayerIndexComponent&& other) = delete;
        PlayerIndexComponent& operator=(const PlayerIndexComponent& other) = delete;
        PlayerIndexComponent& operator=(PlayerIndexComponent&& other) = delete;
    private:
        int m_PlayerIndex;
    };
}


