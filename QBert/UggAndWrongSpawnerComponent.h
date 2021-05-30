#pragma once
#include <BaseComponent.h>

namespace dae
{
	class LevelComponent;
	
	class UggAndWrongSpawnerComponent final : public BaseComponent
	{
	public:
		UggAndWrongSpawnerComponent(LevelComponent* pPyramid);
		virtual ~UggAndWrongSpawnerComponent();

		void Update() override;
		void Render() const override;

		UggAndWrongSpawnerComponent(const UggAndWrongSpawnerComponent& other) = delete;
		UggAndWrongSpawnerComponent(UggAndWrongSpawnerComponent&& other) = delete;
		UggAndWrongSpawnerComponent& operator=(const UggAndWrongSpawnerComponent& other) = delete;
		UggAndWrongSpawnerComponent& operator=(UggAndWrongSpawnerComponent&& other) = delete;

	private:
		LevelComponent* m_pPyramid = nullptr;

		const float m_SpawnInterval = 10.f;
		float m_SpawnTimer = 0.f;
		bool m_SpawnUgg = true;
		
		void SpawnEnemy();
	};
}