#pragma once
#include <BaseComponent.h>

namespace dae
{
	class LevelComponent;

	class SlickAndSamSpawnerComponent final : public BaseComponent
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
		LevelComponent* m_pPyramid = nullptr;

		const float m_SpawnInterval = 5.f;
		float m_SpawnTimer = 0.f;

		void SpawnEnemy() const;
	};
}