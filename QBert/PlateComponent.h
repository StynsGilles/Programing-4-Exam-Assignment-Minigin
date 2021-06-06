#pragma once
#include <BaseComponent.h>

namespace dae
{
	enum class Side;
	class LevelComponent;
	
	class PlateComponent final : public BaseComponent
	{
	public:
		explicit PlateComponent(LevelComponent* pPyramid, int row, Side side);
		~PlateComponent();

		void Initialize() const;
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



