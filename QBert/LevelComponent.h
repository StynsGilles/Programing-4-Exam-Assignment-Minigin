#pragma once
#include <BaseComponent.h>
#include "Texture2D.h"

namespace dae
{
	enum class EnemyType;

	struct LevelCube
	{
		std::vector<std::shared_ptr<Texture2D>> pCubeTextures;
		glm::vec3 position;
		int stage = 0;
		bool reversible = false;
		//std::weak_ptr<GameObject> entity;
		GameObject* entity = nullptr;
	};
	
	class LevelComponent final : public BaseComponent
	{
	public:
		LevelComponent(const std::string& initialColor, const std::string& finalColor, const std::string& interColor = "", bool reversible = false);
		LevelComponent(const std::string& initialColor, const std::string& finalColor, bool reversible);
		virtual ~LevelComponent();

		void Update() override;
		void Render() const override;
		LevelCube* GetTopCube() const;
		LevelCube* GetCube(int row = 0, int col = 0) const;
		int GetRowOfCube(LevelCube* pCurrentCube) const;
		int GetColOfCube(LevelCube* pCurrentCube) const;
		std::pair<int, int> GetRowColOfCube(LevelCube* pCurrentCube) const;
		int GetPyramidSize() const;
		LevelCube* GetNextCubeEnemy(LevelCube* pCurrentCube, int rowChange, int colChange, bool& isOccupied, const EnemyType& enemyType,
			bool& QBertOnCube, bool isSlickOrSam = false) const;
		LevelCube* GetNextCube(LevelCube* pCurrentCube, int rowChange, int colChange,
			bool& fellOfPyramid, bool& positiveChange);
		LevelCube* GetNextCubeNeutral(LevelCube* pCurrentCube, int rowChange, int colChange) const;
		void ClearBoard();
		
		LevelComponent(const LevelComponent& other) = delete;
		LevelComponent(LevelComponent&& other) = delete;
		LevelComponent& operator=(const LevelComponent& other) = delete;
		LevelComponent& operator=(LevelComponent&& other) = delete;

	private:
		static const int m_PyramidSize = 7;
		LevelCube* m_Pyramid[m_PyramidSize][m_PyramidSize];
		bool m_LevelFinished = false;

		void GetNextRowAndCol(LevelCube* pCurrentCube, int& newRow, int& newCol, int rowChange, int colChange) const;
		bool UpdateCubeColor(LevelCube* m_pCube);
		void CheckLevelFinished();
	};
}
