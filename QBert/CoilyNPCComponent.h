#pragma once
#include "EntityComponent.h"
#include "PlateComponent.h"

namespace dae
{
	struct LevelCube;
	class LevelComponent;
	
	enum class CoilyState
	{
		egg,
		normal
	};
	
	class CoilyNPCComponent : public EntityComponent
	{
	public:
		CoilyNPCComponent(LevelComponent* pPyramid, float jumpInterval);
		virtual ~CoilyNPCComponent();

		void Update() override;
		void Render() const override;
		void SetTarget(PlateComponent* pPlate, LevelCube* pCurrentCubeQbert);

		CoilyNPCComponent(const CoilyNPCComponent& other) = delete;
		CoilyNPCComponent(CoilyNPCComponent&& other) = delete;
		CoilyNPCComponent& operator=(const CoilyNPCComponent& other) = delete;
		CoilyNPCComponent& operator=(CoilyNPCComponent&& other) = delete;

	protected:
		CoilyState m_State;

		bool m_GoToPlate = false;
		bool m_ReachedPlateCube = false;
		int m_PlateRow;
		Side m_PlateSide;
		LevelCube* m_PlateDestinationCube;

		void Jump() override;
		void CheckIfBottom();
		virtual void ChasePlayer();
		void GoToPlate();
		LevelCube* GetNextCube(LevelCube* pCoilyCube, LevelCube* pQBertCube, bool& isOccupied, bool& QBertOnCube);
	};
}
