#pragma once
#include "BaseSpawnerComponent.h"

namespace dae
{
	class CoilySpawnerComponent : public BaseSpawnerComponent
	{
	public:
		CoilySpawnerComponent(LevelComponent* pPyramid);
		virtual ~CoilySpawnerComponent();

		void Update() override;
		void Render() const override;

		CoilySpawnerComponent(const CoilySpawnerComponent& other) = delete;
		CoilySpawnerComponent(CoilySpawnerComponent&& other) = delete;
		CoilySpawnerComponent& operator=(const CoilySpawnerComponent& other) = delete;
		CoilySpawnerComponent& operator=(CoilySpawnerComponent&& other) = delete;

	private:
		void SpawnEnemy() override;
	};
}