#pragma once
#include <BaseComponent.h>

namespace dae
{
	enum class EnemyType
	{
		top,
		left,
		right
	};
	
	struct LevelCube;

	class EnemyPositionComponent final : public BaseComponent
	{
	public:
		explicit EnemyPositionComponent(EnemyType enemyType);
		virtual ~EnemyPositionComponent();

		void Update() override;
		void Render() const override;
		void ChangeCube(LevelCube* pNewCube);
		LevelCube* GetCurrentCube() const;
		EnemyType GetEnemyType() const;

		EnemyPositionComponent(const EnemyPositionComponent& other) = delete;
		EnemyPositionComponent(EnemyPositionComponent&& other) = delete;
		EnemyPositionComponent& operator=(const EnemyPositionComponent& other) = delete;
		EnemyPositionComponent& operator=(EnemyPositionComponent&& other) = delete;

	private:
		LevelCube* m_pCurrentCube = nullptr;
		EnemyType m_EnemyType;
		
		void UpdatePosition(const glm::vec3& nextPosition);
	};
}