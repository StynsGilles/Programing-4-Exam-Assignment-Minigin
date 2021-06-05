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
		
        PlayerObserver(const PlayerObserver& other) = delete;
        PlayerObserver(PlayerObserver&& other) = delete;
        PlayerObserver& operator=(const PlayerObserver& other) = delete;
        PlayerObserver& operator=(PlayerObserver&& other) = delete;

	private:

        void UpdateHealthText(GameObject* pEntity);
        void UpdateLivesText(GameObject* pEntity);
        void UpdateScoreText(GameObject* pEntity);
        void HandleFinishedLevel();
    };
}
