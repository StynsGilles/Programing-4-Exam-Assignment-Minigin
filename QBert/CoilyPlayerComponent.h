#pragma once
#include "CoilyNPCComponent.h"

//TODO implement this to handle inputs and jump


namespace dae
{
	class CoilyPlayerComponent : public CoilyNPCComponent
	{
	public:
		CoilyPlayerComponent(LevelComponent* pPyramid, float jumpInterval);
		virtual ~CoilyPlayerComponent();

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