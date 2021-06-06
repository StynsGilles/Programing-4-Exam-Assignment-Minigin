#pragma once
#include "EntityComponent.h"
#include "GameStructs.h"

namespace dae
{
	class QBertComponent;
	class PlateComponent;
	enum class CoilyState;
	struct LevelCube;
	class LevelComponent;
	
	class CoilyNPCComponent : public EntityComponent
	{
	public:
		explicit CoilyNPCComponent(LevelComponent* pPyramid, float jumpInterval);
		virtual ~CoilyNPCComponent();

		void Update() override;
		void Render() const override;
		virtual void SetTarget(PlateComponent* pPlate, LevelCube* pCurrentCubeQbert);

		CoilyNPCComponent(const CoilyNPCComponent& other) = delete;
		CoilyNPCComponent(CoilyNPCComponent&& other) = delete;
		CoilyNPCComponent& operator=(const CoilyNPCComponent& other) = delete;
		CoilyNPCComponent& operator=(CoilyNPCComponent&& other) = delete;

	protected:
		CoilyState m_State = CoilyState::egg;
		
		bool m_ReachedPlateCube = false;
		int m_PlateRow {};
		Side m_PlateSide{};
		LevelCube* m_pPlateDestinationCube = nullptr;

		void Jump() override;
		void CheckIfBottom();
		LevelCube* GetNearestQBertCube(const std::vector<QBertComponent*>& pQBertVec, LevelCube* pCoilyCube) const;
		int GetShortestPathToGoal(const std::pair<int, int>& rowColQBert, std::pair<int, int> rowColCoily) const;
		virtual void ChasePlayer();
		void GoToPlate();
		LevelCube* GetNextCube(LevelCube* pCoilyCube, LevelCube* pQBertCube, bool& isOccupied, bool& QBertOnCube) const;
	};
}
