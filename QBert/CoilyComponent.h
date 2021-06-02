#pragma once
#include "EntityComponent.h"

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

		CoilyComponent(const CoilyComponent& other) = delete;
		CoilyComponent(CoilyComponent&& other) = delete;
		CoilyComponent& operator=(const CoilyComponent& other) = delete;
		CoilyComponent& operator=(CoilyComponent&& other) = delete;

	private:
		CoilyState m_State;
		
		void Jump() override;
		void CheckIfBottom();
		void ChasePlayer();
		LevelCube* GetNextCube(LevelCube* pCoilyCube, LevelCube* pQBertCube, bool& isOccupied, bool& QBertOnCube);
	};
}
