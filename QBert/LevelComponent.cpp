#include "pch.h"
#include "LevelComponent.h"
#include <iostream>
#include <SDL_rect.h>
#include <SDL_render.h>
#include "EnemyPositionComponent.h"
#include "EntityComponent.h"
#include "GameObject.h"
#include "QBertComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlateComponent.h"

dae::LevelComponent::LevelComponent(int pyramidSize, const std::string& initialColor, const std::string& finalColor, const std::string& interColor, bool reversible)
	: m_PyramidSize{pyramidSize}
{
	glm::vec3 initialCubePos = glm::vec3(320, 100, 0);

	auto initialTexture = ResourceManager::GetInstance().LoadTexture("Cube_" + initialColor + ".png");
	std::shared_ptr<Texture2D> interTexture = nullptr;
	if (!interColor.empty())
		interTexture = ResourceManager::GetInstance().LoadTexture("Cube_" + interColor + ".png");
	auto finaltexture = ResourceManager::GetInstance().LoadTexture("Cube_" + finalColor + ".png");
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		std::vector<LevelCube*> newRow;
		for (int col = 0; col <= row; ++col)
		{
			LevelCube* newCube = new LevelCube();
			newCube->pCubeTextures.push_back(initialTexture);
			if (!interColor.empty())
				newCube->pCubeTextures.push_back(interTexture);
			newCube->pCubeTextures.push_back(finaltexture);
			SDL_Rect dst;
			SDL_QueryTexture(newCube->pCubeTextures[newCube->stage]->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
			newCube->position = initialCubePos;
			newCube->reversible = reversible;
			newRow.push_back(newCube);
			if (col == row)
			{
				initialCubePos.x -= (float)dst.w / 2.f + (float)dst.w * col;
				initialCubePos.y += dst.h * 0.75f;
			}
			else
				initialCubePos.x += (float)dst.w;
		}
		m_Pyramid.push_back(newRow);
	}
}

dae::LevelComponent::LevelComponent(int pyramidSize, const std::string& initialColor, const std::string& finalColor, bool reversible)
	:LevelComponent(pyramidSize, initialColor, finalColor, "", reversible)
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
				Renderer::GetInstance().RenderTexture(*m_Pyramid[row][col]->pCubeTextures[m_Pyramid[row][col]->stage], m_Pyramid[row][col]->position.x, m_Pyramid[row][col]->position.y);
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

	if (col >= (int)m_Pyramid[row].size() || col < 0)
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
		case EnemyType::top:
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
	bool& fellOfPyramid, bool& positiveChange, bool& isOccupied, PlateComponent*& pJumpedOnPlate)
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
			isOccupied = true;
		
		positiveChange = UpdateCubeColor(pCube);
		return pCube;
	}
	
	fellOfPyramid = CheckIfJumpedOnPlate(pCurrentCube, rowChange, colChange, pJumpedOnPlate);
	if (pJumpedOnPlate) std::cout << " found the plate!" << std::endl;
	return GetTopCube();
}

bool dae::LevelComponent::CheckIfJumpedOnPlate(LevelCube* pCurrentCube, int rowChange, int colChange, PlateComponent*& pJumpedOnPlate)
{
	if (rowChange == -1)
	{
		auto pAllPlates = SceneManager::GetInstance().GetCurrentScene()->GetAllComponentsOfType<PlateComponent>();
		int newRow = GetRowOfCube(pCurrentCube) + rowChange;
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
				std::cout << "jumped on plate" << std::endl;
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
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto enemies = scene->GetAllComponentsOfType<EnemyPositionComponent>();

	for (auto enemy : enemies)
	{
		enemy->RemoveFromCurrentCube();
		enemy->GetGameObject()->Delete();
	}
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
	else if ((size_t)m_pCube->stage + 1 < m_pCube->pCubeTextures.size())
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
			if ((size_t)m_Pyramid[row][col]->stage + 1 != m_Pyramid[row][col]->pCubeTextures.size())
				levelFinished = false;
		}
	}
	m_LevelFinished = levelFinished;
	if (m_LevelFinished)
	{
		std::cout << "finished level" << std::endl;
		auto* pQbert = SceneManager::GetInstance().GetCurrentScene()->GetComponentOfType<QBertComponent>();
		if (pQbert)
			pQbert->FinishLevel();
	}
}
