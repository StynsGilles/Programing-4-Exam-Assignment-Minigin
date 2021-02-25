#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
    class SubjectComponent final : public BaseComponent
    {
    public:
        SubjectComponent();
        virtual ~SubjectComponent();

        void Update() override;
    	void Render() const override;
    	
        void addObserver(Observer* observer);
        void removeObserver(Observer* observer);
        void Notify(GameObject* object, Event event);
    	
        SubjectComponent(const SubjectComponent& other) = delete;
        SubjectComponent(SubjectComponent&& other) = delete;
        SubjectComponent& operator=(const SubjectComponent& other) = delete;
        SubjectComponent& operator=(SubjectComponent&& other) = delete;
    private:
        std::vector<Observer*> m_pObservers;
    };
}
