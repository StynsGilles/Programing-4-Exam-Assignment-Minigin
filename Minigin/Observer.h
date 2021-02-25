#pragma once

namespace dae
{
    class GameObject;
	
    enum class Event
    {
        PlayerDied,
        PlayerLostHP,
    	IncreaseScore
    };

    class Observer
    {
    public:
        Observer() {}
        virtual ~Observer() {}
        virtual void onNotify(GameObject* entity, Event event) = 0;

        Observer(const Observer& other) = delete;
        Observer(Observer&& other) = delete;
        Observer& operator=(const Observer& other) = delete;
        Observer& operator=(Observer&& other) = delete;
    private:

    };
}

