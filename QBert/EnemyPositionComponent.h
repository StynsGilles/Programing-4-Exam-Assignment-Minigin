#pragma once
#include <BaseComponent.h>

namespace dae
{
	enum class EnemyType;
	class LevelComponent;
	
	struct LevelCube;

	class EnemyPositionComponent final : public BaseComponent
	{
	public:
		explicit EnemyPositionComponent(EnemyType enemyType, LevelComponent* pPyramid);
		~EnemyPositionComponent();

		void Update() override;
		void Render() const override;
		void SpawnOnCube(LevelCube* pNewCube);
		void ChangeCube(LevelCube* pNewCube, bool QBertOnCube);
		void RemoveFromCurrentCube() const;
		LevelCube* GetCurrentCube() const;
		EnemyType GetEnemyType() const;

		EnemyPositionComponent(const EnemyPositionComponent& other) = delete;
		EnemyPositionComponent(EnemyPositionComponent&& other) = delete;
		EnemyPositionComponent& operator=(const EnemyPositionComponent& other) = delete;
		EnemyPositionComponent& operator=(EnemyPositionComponent&& other) = delete;

	private:
		LevelComponent* m_pPyramid = nullptr;
		
		LevelCube* m_pCurrentCube = nullptr;
		EnemyType m_EnemyType;

		void UpdatePosition(const glm::vec3& nextPosition) const;
	};
}