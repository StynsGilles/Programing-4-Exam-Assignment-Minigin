#pragma once
#include <BaseComponent.h>
#include "LevelComponent.h"

namespace dae
{
    class QBertComponent final : public BaseComponent
    {
	public:
		QBertComponent();
		virtual ~QBertComponent();

		void Update() override;
		void Render() const override;
		void ChangeCube(LevelCube* pNewCube);
		LevelCube* GetCurrentCube() const;
    	
		QBertComponent(const QBertComponent& other) = delete;
		QBertComponent(QBertComponent&& other) = delete;
		QBertComponent& operator=(const QBertComponent& other) = delete;
		QBertComponent& operator=(QBertComponent&& other) = delete;

	private:
		LevelCube* m_pCurrentCube = nullptr;

		void UpdatePosition(const glm::vec3& nextPosition);
    };
}



