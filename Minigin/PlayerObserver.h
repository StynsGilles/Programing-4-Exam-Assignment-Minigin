#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
	
	class PlayerObserver final
		: public Observer
		, public BaseComponent
    {
    public:
        PlayerObserver();
        virtual ~PlayerObserver();
    	void onNotify(GameObject* entity, Event event) override;

        void Update() override;
        void Render() const override;
        void SetPosition(float x, float y);
        void InitValues(std::shared_ptr<GameObject> pPlayer);
		
        PlayerObserver(const PlayerObserver& other) = delete;
        PlayerObserver(PlayerObserver&& other) = delete;
        PlayerObserver& operator=(const PlayerObserver& other) = delete;
        PlayerObserver& operator=(PlayerObserver&& other) = delete;

	private:
        int m_PlayerIndex;
        int m_PlayerHealth;
        int m_PlayerMaxHealth;
        int m_PlayerLivesRemaining;
        int m_PlayerScore;
        float m_PosX, m_PosY;
    };
}
