#pragma once

namespace dae
{
    enum class Event
    {
        PlayerDied
    };

    class Observer
    {
    public:
        virtual ~Observer() {}
        virtual void onNotify(GameObject* entity, Event event) = 0;

        Observer(const Observer& other) = delete;
        Observer(Observer&& other) = delete;
        Observer& operator=(const Observer& other) = delete;
        Observer& operator=(Observer&& other) = delete;
    private:

    };
}

