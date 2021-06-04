#include "pch.h"
#include "CoilyComponent.h"
#include "EnemyPositionComponent.h"
#include <GameObject.h>
#include "LevelComponent.h"
#include "QBertComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "SceneManager.h"

dae::CoilyComponent::CoilyComponent(LevelComponent* pPyramid, float jumpInterval)
	: m_State(CoilyState::egg)
	, EntityComponent(pPyramid)
{
	SetJumpRate(jumpInterval);
}

dae::CoilyComponent::~CoilyComponent()
{
}

void dae::CoilyComponent::Update()
{
	JumpUpdate();
}

void dae::CoilyComponent::Render() const
{
}

void dae::CoilyComponent::SetTarget(PlateComponent* pPlate, LevelCube* pCurrentCubeQbert)
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
			int numberOfJumps = 0;
			auto rowColCoily = m_pPyramid->GetRowColOfCube(pCoilyCube);
			bool distanceCalced = false;
			
			while (!distanceCalced)
			{
				std::cout << "calcing path to qbert" << std::endl;
				if (rowColQbert.first < rowColCoily.first &&
					rowColQbert.second < rowColCoily.second)
				{
					rowColCoily.first -= 1;
					rowColCoily.second -= 1;
				}
				else if (rowColQbert.first == rowColCoily.first &&
					rowColQbert.second < rowColCoily.second)
				{
					rowColCoily.first -= 1;
					rowColCoily.second -= 1;
				}
				else if (rowColQbert.first > rowColCoily.first &&
					rowColQbert.second < rowColCoily.second)
					rowColCoily.first = 1;
				else if (rowColQbert.first < rowColCoily.first &&
					rowColQbert.second > rowColCoily.second)
					rowColCoily.first -= 1;
				else if (rowColQbert.first == rowColCoily.first &&
					rowColQbert.second > rowColCoily.second)
					rowColCoily.first -= 1;
				else if (rowColQbert.first > rowColCoily.first &&
					rowColQbert.second > rowColCoily.second)
				{
					rowColCoily.first += 1;
					rowColCoily.second += 1;
				}
				else if (rowColQbert.first < rowColCoily.first &&
					rowColQbert.second == rowColCoily.second)
					rowColCoily.first -= 1;
				else if (rowColQbert.first > rowColCoily.first &&
					rowColQbert.second == rowColCoily.second)
					rowColCoily.first += 1;

				numberOfJumps++;
				if (rowColCoily == rowColQbert)
					distanceCalced = true;
			}
			if (numberOfJumps <= 2)
			{
				m_GoToPlate = true;
				m_PlateDestinationCube = pCurrentCubeQbert;
			}
		}
	}
}

void dae::CoilyComponent::Jump()
{
	switch (m_State)
	{
	case CoilyState::egg:
		JumpRandomDownwards();
		CheckIfBottom();
		break;
	case CoilyState::normal:
		if (m_GoToPlate) GoToPlate();
		else ChasePlayer();
		break;
	default:
		break;
	}
}

void dae::CoilyComponent::CheckIfBottom()
{
	const int pyramidSize = m_pPyramid->GetPyramidSize();
	const int currentRow = m_pPyramid->GetRowOfCube(m_pObject->GetComponent<EnemyPositionComponent>()->GetCurrentCube());

	if (currentRow == pyramidSize-1)
	{
		m_State = CoilyState::normal;
		m_pObject->GetComponent<RenderComponent>()->SetTexture("Coily.png");
	}
}

void dae::CoilyComponent::ChasePlayer()
{
	const auto scene = SceneManager::GetInstance().GetCurrentScene();
	const auto QBert = scene->GetObjectOfType<QBertComponent>();
	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();
	
	if (QBert && pPosComp)
	{
		auto* pQBertComp = QBert->GetComponent<QBertComponent>();
		auto* pQBertCube = pQBertComp->GetCurrentCube();
		auto* pCoilyCube = pPosComp->GetCurrentCube();

		bool isOccupied = false;
		bool QBertOnCube = false;
		LevelCube* pNextCube = GetNextCube(pCoilyCube, pQBertCube, isOccupied, QBertOnCube);
		if (pNextCube && !isOccupied)
			pPosComp->ChangeCube(pNextCube, QBertOnCube);
	}
}

void dae::CoilyComponent::GoToPlate()
{
	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();

	if (pPosComp && m_PlateDestinationCube)
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
				pQbert->KilledCoily();
		}
		else
		{
			LevelCube* pNextCube = GetNextCube(pCoilyCube, m_PlateDestinationCube, isOccupied, QBertOnCube);

			if (pNextCube)
				pPosComp->ChangeCube(pNextCube, false);

			if (pPosComp->GetCurrentCube() == m_PlateDestinationCube)
				m_ReachedPlateCube = true;
		}
	}
}


dae::LevelCube* dae::CoilyComponent::GetNextCube(LevelCube* pCoilyCube, LevelCube* pQBertCube, bool& isOccupied, bool& QBertOnCube)
{
	const auto rowColQbert = m_pPyramid->GetRowColOfCube(pQBertCube);
	const auto rowColCoily = m_pPyramid->GetRowColOfCube(pCoilyCube);

	auto enemyType = m_pObject->GetComponent<EnemyPositionComponent>()->GetEnemyType();
	
	//QBert in a lower column than coily
	if (rowColQbert.first < rowColCoily.first &&
		rowColQbert.second < rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, -1, -1, isOccupied, enemyType, QBertOnCube);
	if (rowColQbert.first == rowColCoily.first &&
		rowColQbert.second < rowColCoily.second)
	{
		LevelCube* pNextCube = nullptr;
		int rowChange = (rand() % 2) * 2 - 1;

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
	if (rowColQbert.first > rowColCoily.first &&
		rowColQbert.second < rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, 1, 0, isOccupied, enemyType, QBertOnCube);
	//QBert in a higher column than coily
	if (rowColQbert.first < rowColCoily.first &&
		rowColQbert.second > rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, -1, 0, isOccupied, enemyType, QBertOnCube);
	if (rowColQbert.first == rowColCoily.first &&
		rowColQbert.second > rowColCoily.second)
	{
		int rowChange = (rand() % 2) * 2 - 1;
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
	if (rowColQbert.first > rowColCoily.first &&
		rowColQbert.second > rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, 1, 1, isOccupied, enemyType, QBertOnCube);
	//QBert in the same column as coily
	if (rowColQbert.first < rowColCoily.first &&
		rowColQbert.second == rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, -1, 0, isOccupied, enemyType, QBertOnCube);
	if (rowColQbert.first > rowColCoily.first &&
		rowColQbert.second == rowColCoily.second)
		return m_pPyramid->GetNextCubeEnemy(pCoilyCube, 1, 0, isOccupied, enemyType, QBertOnCube);

	return nullptr;
}
