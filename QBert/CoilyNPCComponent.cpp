#include "pch.h"
#include "CoilyNPCComponent.h"

#include <GameObject.h>
#include <RenderComponent.h>
#include <Scene.h>
#include <SceneManager.h>
#include <ServiceLocator.h>

#include "EnemyPositionComponent.h"
#include "LevelComponent.h"
#include "PlateComponent.h"
#include "QBertComponent.h"

dae::CoilyNPCComponent::CoilyNPCComponent(LevelComponent* pPyramid, float jumpInterval)
	: EntityComponent(pPyramid)
{
	SetJumpRate(jumpInterval);
}

dae::CoilyNPCComponent::~CoilyNPCComponent()
{
}

void dae::CoilyNPCComponent::Update()
{
	JumpUpdate();
}

void dae::CoilyNPCComponent::Render() const
{
}

void dae::CoilyNPCComponent::SetTarget(PlateComponent* pPlate, LevelCube* pCurrentCubeQbert)
{
	if (m_State == CoilyState::egg)
		return;
	
	m_PlateRow = pPlate->GetRow();
	m_PlateSide = pPlate->GetSide();
	const auto rowColQbert = m_pPyramid->GetRowColOfCube(pCurrentCubeQbert);
	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();

	if (pPosComp)
	{
		auto* pCoilyCube = pPosComp->GetCurrentCube();

		if (pCoilyCube)
		{
			const auto rowColCoily = m_pPyramid->GetRowColOfCube(pCoilyCube);
			const int numberOfJumps = GetShortestPathToGoal(rowColQbert, rowColCoily);

			if (numberOfJumps <= 2)
			{
				m_State = CoilyState::targettedPlate;
				m_pPlateDestinationCube = pCurrentCubeQbert;
			}
		}
	}
}

void dae::CoilyNPCComponent::Jump()
{
	switch (m_State)
	{
	case CoilyState::egg:
		JumpRandomDownwards();
		CheckIfBottom();
		break;
	case CoilyState::normal:
		ChasePlayer();
		break;
	case CoilyState::targettedPlate:
		GoToPlate();
		break;
	default:
		break;
	}
}

void dae::CoilyNPCComponent::CheckIfBottom()
{
	const int pyramidSize = m_pPyramid->GetPyramidSize();
	const int currentRow = m_pPyramid->GetRowOfCube(m_pObject->GetComponent<EnemyPositionComponent>()->GetCurrentCube());

	if (currentRow == pyramidSize-1)
	{
		m_State = CoilyState::normal;
		m_pObject->GetComponent<RenderComponent>()->SetTexture("Coily.png");
	}
}

void dae::CoilyNPCComponent::ChasePlayer()
{
	const auto scene = SceneManager::GetInstance().GetCurrentScene();
	const auto pQBertVec = scene->GetAllComponentsOfType<QBertComponent>();
	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();

	if (pPosComp && !pQBertVec.empty())
	{
		auto* pCoilyCube = pPosComp->GetCurrentCube();
		bool isOccupied = false;
		bool QBertOnCube = false;
		
		if (pQBertVec.size() == 1)
		{
			auto* pQBertCube = pQBertVec[0]->GetCurrentCube();

			LevelCube* pNextCube = GetNextCube(pCoilyCube, pQBertCube, isOccupied, QBertOnCube);
			if (pNextCube && !isOccupied)
				pPosComp->ChangeCube(pNextCube, QBertOnCube);
		}
		else if (pQBertVec.size() == 2)
		{
			auto* pQBertCube = GetNearestQBertCube(pQBertVec, pCoilyCube);
			
			LevelCube* pNextCube = GetNextCube(pCoilyCube, pQBertCube, isOccupied, QBertOnCube);
			if (pNextCube && !isOccupied)
				pPosComp->ChangeCube(pNextCube, QBertOnCube);
		}
	}
}

dae::LevelCube* dae::CoilyNPCComponent::GetNearestQBertCube(const std::vector<QBertComponent*>& pQBertVec,
	LevelCube* pCoilyCube) const
{
	int shortestSteps = 10000;
	LevelCube* pNearestQBertCube = nullptr;
	
	if (pCoilyCube)
	{
		const auto rowColCoily = m_pPyramid->GetRowColOfCube(pCoilyCube);
		
		for (auto* pQBert : pQBertVec)
		{
			auto* pCurrentCubeQbert = pQBert->GetCurrentCube();

			const auto rowColQbert = m_pPyramid->GetRowColOfCube(pCurrentCubeQbert);
			const int numberOfJumps = GetShortestPathToGoal(rowColQbert, rowColCoily);

			if (numberOfJumps < shortestSteps)
			{
				shortestSteps = numberOfJumps;
				pNearestQBertCube = pCurrentCubeQbert;
			}
		}
	}
	return pNearestQBertCube;
}

int dae::CoilyNPCComponent::GetShortestPathToGoal(const std::pair<int, int>& rowColQbert,
	std::pair<int, int> rowColCoily) const
{
	int numberOfJumps = 0;
	bool distanceCalced = false;

	while (!distanceCalced)
	{
		if ((rowColQbert.first < rowColCoily.first && rowColQbert.second < rowColCoily.second) ||
			(rowColQbert.first == rowColCoily.first && rowColQbert.second < rowColCoily.second))
		{
			rowColCoily.first -= 1;
			rowColCoily.second -= 1;
		}
		else if (rowColQbert.first > rowColCoily.first && rowColQbert.second < rowColCoily.second)
			rowColCoily.first += 1;
		else if ((rowColQbert.first < rowColCoily.first && rowColQbert.second > rowColCoily.second) ||
				(rowColQbert.first == rowColCoily.first && rowColQbert.second > rowColCoily.second))
			rowColCoily.first -= 1;
		else if (rowColQbert.first > rowColCoily.first && rowColQbert.second > rowColCoily.second)
		{
			rowColCoily.first += 1;
			rowColCoily.second += 1;
		}
		else if (rowColQbert.first < rowColCoily.first && rowColQbert.second == rowColCoily.second)
			rowColCoily.first -= 1;
		else if (rowColQbert.first > rowColCoily.first && rowColQbert.second == rowColCoily.second)
			rowColCoily.first += 1;

		numberOfJumps++;
		if (rowColCoily.first == rowColQbert.first && rowColCoily.second == rowColQbert.second)
			distanceCalced = true;
	}

	return numberOfJumps;
}

void dae::CoilyNPCComponent::GoToPlate()
{
	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();

	if (pPosComp && m_pPlateDestinationCube)
	{
		bool isOccupied = false;
		bool QBertOnCube = false;
		auto* pCoilyCube = pPosComp->GetCurrentCube();
		if (m_ReachedPlateCube)
		{
			pPosComp->ChangeCube(nullptr, false);
			const auto scene = SceneManager::GetInstance().GetCurrentScene();
			auto* pQbert = scene->GetComponentOfType <QBertComponent>();
			if (pQbert)
			{
				ServiceLocator::GetSoundSystem()->PlaySound("../Data/Sounds/SnakeFall.wav");
				pQbert->KilledCoily();
			}
		}
		else
		{
			LevelCube* pNextCube = GetNextCube(pCoilyCube, m_pPlateDestinationCube, isOccupied, QBertOnCube);

			if (pNextCube)
				pPosComp->ChangeCube(pNextCube, false);

			if (pPosComp->GetCurrentCube() == m_pPlateDestinationCube)
				m_ReachedPlateCube = true;
		}
	}
}


dae::LevelCube* dae::CoilyNPCComponent::GetNextCube(LevelCube* pCoilyCube, LevelCube* pQBertCube, bool& isOccupied, bool& QBertOnCube) const
{
	const auto rowColQbert = m_pPyramid->GetRowColOfCube(pQBertCube);
	const auto rowColCoily = m_pPyramid->GetRowColOfCube(pCoilyCube);

	const auto enemyType = m_pObject->GetComponent<EnemyPositionComponent>()->GetEnemyType();

	//QBert in a lower column than coily
	if (rowColQbert.first < rowColCoily.first && rowColQbert.second < rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, -1, -1, isOccupied, enemyType, QBertOnCube);
	if (rowColQbert.first == rowColCoily.first && rowColQbert.second < rowColCoily.second)
	{
		LevelCube* pNextCube = nullptr;
		const int rowChange = (rand() % 2) * 2 - 1;

		switch (rowChange)
		{
		case -1:
			pNextCube = m_pPyramid->GetNextCubeEnemy(pCoilyCube, rowChange, -1, isOccupied, enemyType, QBertOnCube);
			if (pNextCube)
				return pNextCube;
			return  m_pPyramid->GetNextCubeEnemy(pCoilyCube, -rowChange, 0, isOccupied, enemyType, QBertOnCube);
		case 1:
			pNextCube = m_pPyramid->GetNextCubeEnemy(pCoilyCube, rowChange, 0, isOccupied, enemyType, QBertOnCube);
			if (pNextCube)
				return pNextCube;
			return m_pPyramid->GetNextCubeEnemy(pCoilyCube, -rowChange, -1, isOccupied, enemyType, QBertOnCube);
		default:
			return nullptr;
		}
	}
	if (rowColQbert.first > rowColCoily.first && rowColQbert.second < rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, 1, 0, isOccupied, enemyType, QBertOnCube);
	//QBert in a higher column than coily
	if (rowColQbert.first < rowColCoily.first && rowColQbert.second > rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, -1, 0, isOccupied, enemyType, QBertOnCube);
	if (rowColQbert.first == rowColCoily.first && rowColQbert.second > rowColCoily.second)
	{
		const int rowChange = (rand() % 2) * 2 - 1;
		LevelCube* pNextCube;
		switch (rowChange)
		{
		case -1:
			pNextCube = m_pPyramid->GetNextCubeEnemy(pCoilyCube, rowChange, 0, isOccupied, enemyType, QBertOnCube);
			if (pNextCube)
				return pNextCube;
			return m_pPyramid->GetNextCubeEnemy(pCoilyCube, -rowChange, 1, isOccupied, enemyType, QBertOnCube);
		case 1:
			pNextCube = m_pPyramid->GetNextCubeEnemy(pCoilyCube, rowChange, 1, isOccupied, enemyType, QBertOnCube);
			if (pNextCube)
				return pNextCube;
			return m_pPyramid->GetNextCubeEnemy(pCoilyCube, -rowChange, 0, isOccupied, enemyType, QBertOnCube);
		default:
			return nullptr;
		}
	}
	if (rowColQbert.first > rowColCoily.first && rowColQbert.second > rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, 1, 1, isOccupied, enemyType, QBertOnCube);
	//QBert in the same column as coily
	if (rowColQbert.first < rowColCoily.first && rowColQbert.second == rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, -1, 0, isOccupied, enemyType, QBertOnCube);
	if (rowColQbert.first > rowColCoily.first && rowColQbert.second == rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, 1, 0, isOccupied, enemyType, QBertOnCube);

	return nullptr;
}
