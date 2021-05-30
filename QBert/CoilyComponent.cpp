#include "pch.h"
#include "CoilyComponent.h"
#include "EnemyPositionComponent.h"
#include <GameObject.h>
#include "LevelComponent.h"
#include "QBertComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "SceneManager.h"

dae::CoilyComponent::CoilyComponent(LevelComponent* pPyramid)
	: m_State(CoilyState::egg)
	, EntityComponent(pPyramid)
{
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

void dae::CoilyComponent::Jump()
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
	default:
		break;
	}
}

void dae::CoilyComponent::CheckIfBottom()
{
	int pyramidSize = m_pPyramid->GetPyramidSize();

	int currentRow = m_pPyramid->GetRowOfCube(m_pObject->GetComponent<EnemyPositionComponent>()->GetCurrentCube());

	if (currentRow == pyramidSize-1)
	{
		m_State = CoilyState::normal;
		m_pObject->GetComponent<RenderComponent>()->SetTexture("Coily.png");
	}
}

void dae::CoilyComponent::ChasePlayer()
{
	auto scene = SceneManager::GetInstance().GetCurrentScene();
	auto QBert = scene->GetObjectOfType<QBertComponent>();
	auto* pPosComp = m_pObject->GetComponent<EnemyPositionComponent>();
	
	if (QBert && pPosComp)
	{
		auto* pQBertComp = QBert->GetComponent<QBertComponent>();
		auto* pQBertCube = pQBertComp->GetCurrentCube();
		auto* pCoilyCube = pPosComp->GetCurrentCube();
		
		const auto rowColQbert = m_pPyramid->GetRowColOfCube(pQBertCube);
		const auto rowColCoily = m_pPyramid->GetRowColOfCube(pCoilyCube);

		int rowChange = 0;
		int colChange = 0;
		
		//QBert in a lower column than coily
		if (rowColQbert.first < rowColCoily.first &&
			rowColQbert.second < rowColCoily.second)
		{
			rowChange = -1;
			colChange = -1;
			
		}
		else if (rowColQbert.first == rowColCoily.first &&
			rowColQbert.second < rowColCoily.second)
		{
			rowChange = (rand() % 2) * 2 - 1;
			switch (rowChange)
			{
			case -1:
				colChange = -1;
				break;
			case 1:
				colChange = 0;
				break;
			default:
				break;
			}
			
		}
		else if (rowColQbert.first > rowColCoily.first &&
			rowColQbert.second < rowColCoily.second)
		{
			rowChange = 1;
		}
		//QBert in a higher column than coily
		else if (rowColQbert.first < rowColCoily.first &&
			rowColQbert.second > rowColCoily.second)
		{
			rowChange = -1;
		}
		else if (rowColQbert.first == rowColCoily.first &&
			rowColQbert.second > rowColCoily.second)
		{
			rowChange = (rand() % 2) * 2 - 1;
			switch (rowChange)
			{
			case -1:
				colChange = 0;
				break;
			case 1:
				colChange = 1;
				break;
			default:
				break;
			}
		}
		else if (rowColQbert.first > rowColCoily.first &&
			rowColQbert.second > rowColCoily.second)
		{
			rowChange = 1;
			colChange = rand()%2;
		}
		//QBert in the same column as coily
		else if (rowColQbert.first < rowColCoily.first &&
			rowColQbert.second == rowColCoily.second)
		{
			rowChange = -1;
		}
		else if (rowColQbert.first > rowColCoily.first &&
			rowColQbert.second == rowColCoily.second)
		{
			rowChange = 1;
		}
		// same cube
		else if (rowColQbert.first == rowColCoily.first &&
			rowColQbert.second == rowColCoily.second)
		{
			//nothing for now
		}

		std::cout << "jumping in the direction of row change: " << rowChange << " and col change: " << colChange << std::endl;

		LevelCube* pNextCube = m_pPyramid->GetNextCubeEnemy(pCoilyCube, rowChange, colChange);
		pPosComp->ChangeCube(pNextCube);
	}
}
