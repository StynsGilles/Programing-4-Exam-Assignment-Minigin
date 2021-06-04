#pragma once
#include <BaseComponent.h>
#include "LevelComponent.h"

namespace dae
{
    class QBertComponent final : public BaseComponent
    {
	public:
		QBertComponent(LevelComponent* pPyramid, float jumpInterval);
		virtual ~QBertComponent();

		void Update() override;
		void Render() const override;
		void ChangeCube(LevelCube* pNewCube, bool fellOf, bool positiveChange, bool isOccupied);
		LevelCube* GetCurrentCube() const;
		void KillGreen() const;
		void KilledCoily() const;
		void FlippedTile() const;
		void FinishLevel() const;
		void Move(int rowChange, int colChange);
    	
		QBertComponent(const QBertComponent& other) = delete;
		QBertComponent(QBertComponent&& other) = delete;
		QBertComponent& operator=(const QBertComponent& other) = delete;
		QBertComponent& operator=(QBertComponent&& other) = delete;

	private:
		LevelCube* m_pCurrentCube = nullptr;
		LevelComponent* m_pPyramid = nullptr;

		bool m_CanJump = true;
		const float m_JumpInterval;
		float m_JumpCoolDown;
    	
		const int m_ScorePerCubeChange = 25;
		const int m_ScoreCoilyDefeat = 500;
		const int m_ScoreRemainingDisc = 50;
		const int m_ScoreSlAndSaDefeat = 300;

		void ModifyCoilyBehavior(PlateComponent* pPlate);
		void UpdatePosition(const glm::vec3& nextPosition);
		void AwardScore(int amount) const;
    };
}



