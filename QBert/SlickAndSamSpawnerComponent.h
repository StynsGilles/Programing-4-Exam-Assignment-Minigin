#pragma once
#include "BaseSpawnerComponent.h"

namespace dae
{
	class LevelComponent;

	class SlickAndSamSpawnerComponent final : public BaseSpawnerComponent
	{
	public:
		SlickAndSamSpawnerComponent(LevelComponent* pPyramid);
		virtual ~SlickAndSamSpawnerComponent();

		void Update() override;
		void Render() const override;
		
		SlickAndSamSpawnerComponent(const SlickAndSamSpawnerComponent& other) = delete;
		SlickAndSamSpawnerComponent(SlickAndSamSpawnerComponent&& other) = delete;
		SlickAndSamSpawnerComponent& operator=(const SlickAndSamSpawnerComponent& other) = delete;
		SlickAndSamSpawnerComponent& operator=(SlickAndSamSpawnerComponent&& other) = delete;

	private:
		bool m_SpawnSlick = true;

		void SpawnEnemy() override;
	};
}