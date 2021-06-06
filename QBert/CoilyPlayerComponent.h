#pragma once
#include "CoilyNPCComponent.h"

namespace dae
{
	class CoilyPlayerComponent final : public CoilyNPCComponent
	{
	public:
		explicit CoilyPlayerComponent(LevelComponent* pPyramid, float jumpInterval);
		~CoilyPlayerComponent();

		void Move(int rowChange, int colChange);
		void SetTarget(PlateComponent* pPlate, LevelCube* pCurrentCubeQbert) override;
		
		CoilyPlayerComponent(const CoilyPlayerComponent& other) = delete;
		CoilyPlayerComponent(CoilyPlayerComponent&& other) = delete;
		CoilyPlayerComponent& operator=(const CoilyPlayerComponent& other) = delete;
		CoilyPlayerComponent& operator=(CoilyPlayerComponent&& other) = delete;

	private:
		bool m_CanJump = false;
		
		void ChasePlayer() override;
	};
}