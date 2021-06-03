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
	
	class CoilyComponent  final : public EntityComponent
	{
	public:
		CoilyComponent(LevelComponent* pPyramid);
		virtual ~CoilyComponent();

		void Update() override;
		void Render() const override;
		void SetTarget(PlateComponent* pPlate, LevelCube* pCurrentCubeQbert);

		CoilyComponent(const CoilyComponent& other) = delete;
		CoilyComponent(CoilyComponent&& other) = delete;
		CoilyComponent& operator=(const CoilyComponent& other) = delete;
		CoilyComponent& operator=(CoilyComponent&& other) = delete;

	private:
		CoilyState m_State;

		bool m_GoToPlate = false;
		bool m_ReachedPlateCube = false;
		int m_PlateRow;
		Side m_PlateSide;
		LevelCube* m_PlateDestinationCube;

		void Jump() override;
		void CheckIfBottom();
		void ChasePlayer();
		void GoToPlate();
		LevelCube* GetNextCube(LevelCube* pCoilyCube, LevelCube* pQBertCube, bool& isOccupied, bool& QBertOnCube);
	};
}
