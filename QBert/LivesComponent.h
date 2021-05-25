#pragma once
#include <BaseComponent.h>

namespace dae
{
	class LivesComponent final : public BaseComponent
	{
    public:
        LivesComponent(int maxLives);
        virtual ~LivesComponent();

        void Update() override;
        void Render() const override;
        
        void LoseLives(int amount);
        int GetLivesRemaining() const;

        LivesComponent(const LivesComponent& other) = delete;
        LivesComponent(LivesComponent&& other) = delete;
        LivesComponent& operator=(const LivesComponent& other) = delete;
        LivesComponent& operator=(LivesComponent&& other) = delete;
    private:
        int m_MaxLives;
        int m_LivesRemaining;
	};
}