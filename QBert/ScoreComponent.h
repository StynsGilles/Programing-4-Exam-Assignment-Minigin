#pragma once
#include <BaseComponent.h>

namespace dae
{
    class ScoreComponent final : public BaseComponent
    {
    public:
        ScoreComponent();
        virtual ~ScoreComponent();

        void Update() override;
    	void Render() const override;
    	
        void AddToScore(int score);
        int GetScore() const;
    	
        ScoreComponent(const ScoreComponent& other) = delete;
        ScoreComponent(ScoreComponent&& other) = delete;
        ScoreComponent& operator=(const ScoreComponent& other) = delete;
        ScoreComponent& operator=(ScoreComponent&& other) = delete;
    private:
        int m_Score;
    };
}