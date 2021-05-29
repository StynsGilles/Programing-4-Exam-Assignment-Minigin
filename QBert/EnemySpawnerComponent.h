#pragma once
#include <BaseComponent.h>

namespace dae
{
	class EnemySpawnerComponent : public BaseComponent
	{
	public:
		EnemySpawnerComponent();
		virtual ~EnemySpawnerComponent();

		void Update() override;
		void Render() const override;

		EnemySpawnerComponent(const EnemySpawnerComponent& other) = delete;
		EnemySpawnerComponent(EnemySpawnerComponent&& other) = delete;
		EnemySpawnerComponent& operator=(const EnemySpawnerComponent& other) = delete;
		EnemySpawnerComponent& operator=(EnemySpawnerComponent&& other) = delete;

	private:
	};
}