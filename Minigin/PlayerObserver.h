#pragma once
#include "Observer.h"

namespace dae
{
	class GameObject;
	
	class PlayerObserver final : public Observer
    {
    public:
        PlayerObserver();
        virtual ~PlayerObserver();
    	void onNotify(GameObject* entity, Event event) override;

        PlayerObserver(const PlayerObserver& other) = delete;
        PlayerObserver(PlayerObserver&& other) = delete;
        PlayerObserver& operator=(const PlayerObserver& other) = delete;
        PlayerObserver& operator=(PlayerObserver&& other) = delete;
    private:

    };
}
