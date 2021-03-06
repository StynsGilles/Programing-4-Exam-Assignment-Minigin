#include "pch.h"
#include "LevelComponent.h"

#include <GameObject.h>
#include <Renderer.h>
#include <ResourceManager.h>
#include <Scene.h>
#include <SceneManager.h>

#include "EnemyPositionComponent.h"
#include "GameStructs.h"
#include "PlateComponent.h"
#include "QBertComponent.h"

dae::LevelComponent::LevelComponent(int pyramidSize, float cubeWidth, float cubeHeight, const std::string& initialColor, const std::string& finalColor, const std::string& interColor, bool reversible)
	: m_PyramidSize{pyramidSize}
	, m_CubeWidth{cubeWidth}
	, m_CubeHeight{cubeHeight}
{
	glm::vec3 initialCubePos = glm::vec3(320, 50, 0);

	const auto pInitialTexture = ResourceManager::GetInstance().LoadTexture("Cube_" + initialColor + ".png");
	std::shared_ptr<Texture2D> pInterTexture = nullptr;
	if (!interColor.empty())
		pInterTexture = ResourceManager::GetInstance().LoadTexture("Cube_" + interColor + ".png");
	const auto pFinalTexture = ResourceManager::GetInstance().LoadTexture("Cube_" + finalColor + ".png");
	
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		std::vector<LevelCube*> newRow;
		for (int col = 0; col <= row; ++col)
		{
			auto* pNewCube = new LevelCube();
			pNewCube->pCubeTextures.push_back(pInitialTexture);
			if (!interColor.empty())
				pNewCube->pCubeTextures.push_back(pInterTexture);
			pNewCube->pCubeTextures.push_back(pFinalTexture);
			
			pNewCube->position = initialCubePos;
			pNewCube->reversible = reversible;
			newRow.push_back(pNewCube);
			if (col == row)
			{
				initialCubePos.x -= m_CubeWidth / 2.f + m_CubeWidth * col;
				initialCubePos.y += m_CubeHeight * 0.75f;
			}
			else
				initialCubePos.x += m_CubeWidth;
		}
		m_Pyramid.push_back(newRow);
	}
}

dae::LevelComponent::LevelComponent(int pyramidSize, float cubeWidth, float cubeHeight, const std::string& initialColor, const std::string& finalColor, bool reversible)
	:LevelComponent(pyramidSize, cubeWidth, cubeHeight, initialColor, finalColor, "", reversible)
{}

dae::LevelComponent::~LevelComponent()
{
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		for (int col = 0; col <= row; ++col)
		{
			if (m_Pyramid[row][col])
				delete m_Pyramid[row][col];
		}
	}
}

void dae::LevelComponent::Update()
{
}

void dae::LevelComponent::Render() const
{
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		for (int col = 0; col <= row; ++col)
		{
			if (m_Pyramid[row][col]->pCubeTextures[m_Pyramid[row][col]->stage])
				Renderer::GetInstance().RenderTexture(*m_Pyramid[row][col]->pCubeTextures[m_Pyramid[row][col]->stage], m_Pyramid[row][col]->position.x, m_Pyramid[row][col]->position.y, m_CubeWidth, m_CubeHeight);
		}
	}
}

dae::LevelCube* dae::LevelComponent::GetTopCube() const
{
	return m_Pyramid[0][0];
}

dae::LevelCube* dae::LevelComponent::GetCube(int row, int col) const
{
	if (row >= m_PyramidSize || row < 0)
		return nullptr;

	if (col >= static_cast<int>(m_Pyramid[row].size()) || col < 0)
		return nullptr;
	
	return m_Pyramid[row][col];
}

int dae::LevelComponent::GetRowOfCube(LevelCube* pCurrentCube) const
{
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		for (int col = 0; col <= row; ++col)
		{
			if (m_Pyramid[row][col] == pCurrentCube)
				return row;
		}
	}
	return -1;
}

int dae::LevelComponent::GetColOfCube(LevelCube* pCurrentCube) const
{
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		for (int col = 0; col <= row; ++col)
		{
			if (m_Pyramid[row][col] == pCurrentCube)
				return col;
		}
	}
	return -1;
}

std::pair<int, int> dae::LevelComponent::GetRowColOfCube(LevelCube* pCurrentCube) const
{
	return std::make_pair(GetRowOfCube(pCurrentCube), GetColOfCube(pCurrentCube));
}

int dae::LevelComponent::GetPyramidSize() const
{
	return m_PyramidSize;
}

dae::LevelCube* dae::LevelComponent::GetNextCubeEnemy(LevelCube* pCurrentCube, int rowChange, int colChange, bool& isOccupied,
	const EnemyType& enemyType, bool& QBertOnCube, bool isSlickOrSam) const
{
	auto* pCube = GetNextCubeNeutral(pCurrentCube, rowChange, colChange);

	if (pCube)
	{
		switch (enemyType)
		{
		case EnemyType::left:
		{
			auto* pLeftCube = GetNextCubeNeutral(pCube, 1, 0);
			if (pLeftCube && pLeftCube->entity)
			{
				if (pLeftCube->entity->GetComponent<QBertComponent>())
					QBertOnCube = true;
				else
				{
					QBertOnCube = false;
					isOccupied = true;
					return nullptr;
				}
			}
			isOccupied = false;
		}
		break;
		case EnemyType::right:
		{
			auto* pRightCube = GetNextCubeNeutral(pCube, 1, 1);
			if (pRightCube && pRightCube->entity)
			{
				if (pRightCube->entity->GetComponent<QBertComponent>())
					QBertOnCube = true;
				else
				{
					QBertOnCube = false;
					isOccupied = true;
					return nullptr;
				}
			}
			isOccupied = false;
		}
		break;
		case EnemyType::top:
		default:
			if (pCube->entity)
			{
				if (pCube->entity->GetComponent<QBertComponent>())
					QBertOnCube = true;
				else
				{
					QBertOnCube = false;
					isOccupied = true;
					return nullptr;
				}
			}
			isOccupied = false;

			if (isSlickOrSam)
				pCube->stage = 0;
			break;
		}
	}

	return pCube;
}

dae::LevelCube* dae::LevelComponent::GetNextCube(LevelCube* pCurrentCube, int rowChange, int colChange, 
	bool& fellOfPyramid, bool& positiveChange, bool& isOccupied, bool& otherPlayerOnCube, PlateComponent*& pJumpedOnPlate)
{	
	auto* pCube = GetNextCubeNeutral(pCurrentCube, rowChange, colChange);
	
	if (pCube == nullptr)
	{
		fellOfPyramid = CheckIfJumpedOnPlate(pCurrentCube, rowChange, colChange, pJumpedOnPlate);
		return GetTopCube();
	}

	if (pCube)
	{
		if (pCube->entity)
		{
			isOccupied = true;
			if (pCube->entity->GetComponent<QBertComponent>())
				otherPlayerOnCube = true;
		}
		
		positiveChange = UpdateCubeColor(pCube);
		return pCube;
	}
	
	fellOfPyramid = CheckIfJumpedOnPlate(pCurrentCube, rowChange, colChange, pJumpedOnPlate);
	return GetTopCube();
}

bool dae::LevelComponent::CheckIfJumpedOnPlate(LevelCube* pCurrentCube, int rowChange, int colChange, PlateComponent*& pJumpedOnPlate) const
{
	if (rowChange == -1)
	{
		auto pAllPlates = SceneManager::GetInstance().GetCurrentScene()->GetAllComponentsOfType<PlateComponent>();
		const int newRow = GetRowOfCube(pCurrentCube) + rowChange;
		Side sideNeeded{};

		switch (colChange)
		{
		case -1:
			sideNeeded = Side::left;
			break;
		case 0:
			sideNeeded = Side::right;
			break;
		default:
			break;
		}

		for (auto* plate : pAllPlates)
		{
			if (newRow == plate->GetRow() && sideNeeded == plate->GetSide())
			{
				pJumpedOnPlate = plate;
				return false;
			}
		}
	}
	return true;
}

dae::LevelCube* dae::LevelComponent::GetNextCubeNeutral(LevelCube* pCurrentCube, int rowChange, int colChange) const
{
	int newRow = -1;
	int	newCol = -1;

	GetNextRowAndCol(pCurrentCube, newRow, newCol, rowChange, colChange);
	auto* pCube = GetCube(newRow, newCol);

	return pCube;
}

void dae::LevelComponent::ClearBoard()
{
	const auto pScene = SceneManager::GetInstance().GetCurrentScene();
	auto enemies = pScene->GetAllComponentsOfType<EnemyPositionComponent>();

	for (auto* pEnemy : enemies)
	{
		pEnemy->RemoveFromCurrentCube();
		pEnemy->GetGameObject()->Delete();
	}
}

float dae::LevelComponent::GetCubeWidth() const
{
	return m_CubeWidth;
}

float dae::LevelComponent::GetCubeHeight() const
{
	return m_CubeHeight;
}

void dae::LevelComponent::GetNextRowAndCol(LevelCube* pCurrentCube, int& newRow, int& newCol, int rowChange, int colChange) const
{
	int currentRow = -1;
	int currentCol = -1;
	
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		for (int col = 0; col <= row; ++col)
		{
			if (m_Pyramid[row][col] == pCurrentCube)
			{
				currentRow = row;
				currentCol = col;
			}
		}
	}

	newRow = currentRow + rowChange;
	newCol = currentCol + colChange;
}

bool dae::LevelComponent::UpdateCubeColor(LevelCube* m_pCube)
{
	if (m_pCube->reversible)
	{
		switch (m_pCube->stage)
		{
		case 0:
			m_pCube->stage++;
			CheckLevelFinished();
			return true;
		case 1:
			m_pCube->stage--;
			return false;
		default:
			return false;
		}
	}
	else if (static_cast<size_t>(m_pCube->stage) + 1 < m_pCube->pCubeTextures.size())
	{
		m_pCube->stage++;
		CheckLevelFinished();
		return true;
	}
	return false;
}

void dae::LevelComponent::CheckLevelFinished()
{
	bool levelFinished = true;
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		for (int col = 0; col <= row; ++col)
		{
			if (static_cast<size_t>(m_Pyramid[row][col]->stage) + 1 != m_Pyramid[row][col]->pCubeTextures.size())
				levelFinished = false;
		}
	}
	m_LevelFinished = levelFinished;
	if (m_LevelFinished)
	{
		auto* pQbert = SceneManager::GetInstance().GetCurrentScene()->GetComponentOfType<QBertComponent>();
		if (pQbert)
			pQbert->FinishLevel();
	}
}
