#pragma once
#include <BaseComponent.h>
#include <Observer.h>

namespace dae
{
	class GameObject;
	
	class PlayerObserver final
		: public Observer
    {
    public:
        PlayerObserver();
        virtual ~PlayerObserver();
    	void onNotify(GameObject* pEntity, Event event) override;
        
        void SetHealthObject(std::shared_ptr<GameObject> pHealth);
        void SetLivesObject(std::shared_ptr<GameObject> pLives);
        void SetScorebject(std::shared_ptr<GameObject> pScore);
		
        PlayerObserver(const PlayerObserver& other) = delete;
        PlayerObserver(PlayerObserver&& other) = delete;
        PlayerObserver& operator=(const PlayerObserver& other) = delete;
        PlayerObserver& operator=(PlayerObserver&& other) = delete;

	private:
        std::shared_ptr<GameObject> m_HealthObject;
        std::shared_ptr<GameObject> m_LivesObject;
        std::shared_ptr<GameObject> m_ScoreObject;

        void UpdateHealthText(GameObject* pEntity);
        void UpdateLivesText(GameObject* pEntity);
        void UpdateScoreText(GameObject* pEntity);
    };
}
