#pragma once
#include "BaseSpawnerComponent.h"

namespace dae
{
	class LevelComponent;
	
	class UggAndWrongSpawnerComponent final : public BaseSpawnerComponent
	{
	public:
		UggAndWrongSpawnerComponent(LevelComponent* pPyramid, float spawnInterval, float jumpCooldown);
		virtual ~UggAndWrongSpawnerComponent();

		void Update() override;
		void Render() const override;

		UggAndWrongSpawnerComponent(const UggAndWrongSpawnerComponent& other) = delete;
		UggAndWrongSpawnerComponent(UggAndWrongSpawnerComponent&& other) = delete;
		UggAndWrongSpawnerComponent& operator=(const UggAndWrongSpawnerComponent& other) = delete;
		UggAndWrongSpawnerComponent& operator=(UggAndWrongSpawnerComponent&& other) = delete;

	private:
		bool m_SpawnUgg = true;
		
		void SpawnEnemy() override;
	};
}