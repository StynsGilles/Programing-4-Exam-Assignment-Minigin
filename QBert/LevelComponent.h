#pragma once
#include <BaseComponent.h>

namespace dae
{
	struct LevelCube;
	class PlateComponent;
	enum class EnemyType;
	
	class LevelComponent final : public BaseComponent
	{
	public:
		explicit LevelComponent(int pyramidSize, float cubeWidth, float cubeHeight, const std::string& initialColor, const std::string& finalColor, const std::string& interColor = "", bool reversible = false);
		explicit LevelComponent(int pyramidSize, float cubeWidth, float cubeHeight, const std::string& initialColor, const std::string& finalColor, bool reversible);
		~LevelComponent() override;

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
			bool& fellOfPyramid, bool& positiveChange, bool& isOccupied, bool& otherPlayerOnCube, PlateComponent*& pJumpedOnPlate);
		LevelCube* GetNextCubeNeutral(LevelCube* pCurrentCube, int rowChange, int colChange) const;
		void ClearBoard();
		float GetCubeWidth() const;
		float GetCubeHeight() const;
		
		LevelComponent(const LevelComponent& other) = delete;
		LevelComponent(LevelComponent&& other) = delete;
		LevelComponent& operator=(const LevelComponent& other) = delete;
		LevelComponent& operator=(LevelComponent&& other) = delete;

	private:
		int m_PyramidSize = 7;
		float m_CubeWidth;
		float m_CubeHeight;
		std::vector<std::vector<LevelCube*>> m_Pyramid;
		bool m_LevelFinished = false;

		bool CheckIfJumpedOnPlate(LevelCube* pCurrentCube, int rowChange, int colChange, PlateComponent*& pJumpedOnPlate) const;
		void GetNextRowAndCol(LevelCube* pCurrentCube, int& newRow, int& newCol, int rowChange, int colChange) const;
		bool UpdateCubeColor(LevelCube* m_pCube);
		void CheckLevelFinished();
	};
}
