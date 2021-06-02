#pragma once
#include <BaseComponent.h>
#include "LevelComponent.h"

namespace dae
{
    class QBertComponent final : public BaseComponent
    {
	public:
		QBertComponent();
		virtual ~QBertComponent();

		void Update() override;
		void Render() const override;
		void ChangeCube(LevelCube* pNewCube, bool fellOf, bool positiveChange);
		LevelCube* GetCurrentCube() const;
		void KillGreen() const;
    	
		QBertComponent(const QBertComponent& other) = delete;
		QBertComponent(QBertComponent&& other) = delete;
		QBertComponent& operator=(const QBertComponent& other) = delete;
		QBertComponent& operator=(QBertComponent&& other) = delete;

	private:
		LevelCube* m_pCurrentCube = nullptr;

		const int m_ScorePerCubeChange = 25;
		const int m_ScoreCoilyDefeat = 500;
		const int m_ScoreRemainingDisc = 50;
		const int m_ScoreSlAndSaDefeat = 300;
    	
		void UpdatePosition(const glm::vec3& nextPosition);
    };
}



