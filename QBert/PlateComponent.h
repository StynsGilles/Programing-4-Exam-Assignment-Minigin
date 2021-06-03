#pragma once
#include <BaseComponent.h>

namespace dae
{
	class LevelComponent;

	enum class Side
	{
		left,
		right
	};
	
	class PlateComponent : public BaseComponent
	{
	public:
		PlateComponent(LevelComponent* pPyramid, int row, Side side);
		virtual ~PlateComponent();

		void Initialize();
		void Update() override;
		void Render() const override;
		int GetRow() const;
		Side GetSide() const;
		
		PlateComponent(const PlateComponent& other) = delete;
		PlateComponent(PlateComponent&& other) = delete;
		PlateComponent& operator=(const PlateComponent& other) = delete;
		PlateComponent& operator=(PlateComponent&& other) = delete;
	private:
		LevelComponent* m_pPyramid = nullptr;

		Side m_Side;
		int m_Row;
	};
}



