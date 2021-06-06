#pragma once
#include "BaseComponent.h"

namespace dae
{
	enum class Event;
	class Observer;

	class SubjectComponent final : public BaseComponent
    {
    public:
        explicit SubjectComponent();
        ~SubjectComponent();

        void Update() override;
    	void Render() const override;
    	
        void AddObserver(std::shared_ptr<Observer> observer);
        void RemoveObserver(std::shared_ptr<Observer> observer);
        void Notify(GameObject* object, Event event);
    	
        SubjectComponent(const SubjectComponent& other) = delete;
        SubjectComponent(SubjectComponent&& other) = delete;
        SubjectComponent& operator=(const SubjectComponent& other) = delete;
        SubjectComponent& operator=(SubjectComponent&& other) = delete;
    private:
        std::vector<std::shared_ptr<Observer>> m_pObservers;
    };
}
