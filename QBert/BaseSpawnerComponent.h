#pragma once
#include <BaseComponent.h>

namespace dae
{
	class LevelComponent;

	class BaseSpawnerComponent : public BaseComponent
	{
	public:
		BaseSpawnerComponent(LevelComponent* pPyramid);
		virtual ~BaseSpawnerComponent();

		virtual void Update() override;
		virtual void Render() const override = 0;

		static void Spawn();

		BaseSpawnerComponent(const BaseSpawnerComponent& other) = delete;
		BaseSpawnerComponent(BaseSpawnerComponent&& other) = delete;
		BaseSpawnerComponent& operator=(const BaseSpawnerComponent& other) = delete;
		BaseSpawnerComponent& operator=(BaseSpawnerComponent&& other) = delete;
	protected:
		LevelComponent* m_pPyramid = nullptr;

		const float m_SpawnInterval = 10.f;
		float m_SpawnTimer = 0.f;

		virtual void SpawnEnemy() = 0;
	};
}


