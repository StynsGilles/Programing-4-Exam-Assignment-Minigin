#pragma once
#include <BaseComponent.h>

namespace dae
{
	struct LevelCube;

	class EnemyPositionComponent final : public BaseComponent
	{
	public:
		EnemyPositionComponent();
		virtual ~EnemyPositionComponent();

		void Update() override;
		void Render() const override;
		void ChangeCube(LevelCube* pNewCube);
		LevelCube* GetCurrentCube() const;

		EnemyPositionComponent(const EnemyPositionComponent& other) = delete;
		EnemyPositionComponent(EnemyPositionComponent&& other) = delete;
		EnemyPositionComponent& operator=(const EnemyPositionComponent& other) = delete;
		EnemyPositionComponent& operator=(EnemyPositionComponent&& other) = delete;

	private:
		LevelCube* m_pCurrentCube = nullptr;
		
		void UpdatePosition(const glm::vec3& nextPosition);
	};
}