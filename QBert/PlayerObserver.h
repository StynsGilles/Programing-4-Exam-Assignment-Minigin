#pragma once
#include <Observer.h>

namespace dae
{
	class GameObject;
	
	class PlayerObserver final : public Observer
    {
    public:
        explicit PlayerObserver();
        ~PlayerObserver();

		void onNotify(GameObject* pEntity, Event event) override;
		
        PlayerObserver(const PlayerObserver& other) = delete;
        PlayerObserver(PlayerObserver&& other) = delete;
        PlayerObserver& operator=(const PlayerObserver& other) = delete;
        PlayerObserver& operator=(PlayerObserver&& other) = delete;

	private:
        void UpdateLivesText(GameObject* pEntity) const;
        void UpdateScoreText(GameObject* pEntity) const;
        void HandleFinishedLevel() const;
    };
}
