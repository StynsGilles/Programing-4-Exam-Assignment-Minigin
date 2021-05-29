#pragma once
#include <BaseComponent.h>

namespace dae
{	
	class HealthComponent final : public BaseComponent
    {
    public:
        HealthComponent();
        virtual ~HealthComponent();

		void Update() override;
		void Render() const override;

        void Damage(int amount);
        void LoseLives(int amount);
        int GetHealth() const;
        int GetMaxHealth() const;
        int GetLivesRemaining() const;
		
        HealthComponent(const HealthComponent& other) = delete;
        HealthComponent(HealthComponent&& other) = delete;
        HealthComponent& operator=(const HealthComponent& other) = delete;
        HealthComponent& operator=(HealthComponent&& other) = delete;
    private:
        int m_MaxHealth;
        int m_CurrentHealth;
        int m_MaxLives;
        int m_LivesRemaining;
    };
}
