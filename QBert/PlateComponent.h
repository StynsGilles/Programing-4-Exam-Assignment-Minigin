#pragma once
#include <BaseComponent.h>

namespace dae
{
	class PlateComponent : public BaseComponent
	{
	public:
		PlateComponent();
		virtual ~PlateComponent();

		void Update() override;
		void Render() const override;

		PlateComponent(const PlateComponent& other) = delete;
		PlateComponent(PlateComponent&& other) = delete;
		PlateComponent& operator=(const PlateComponent& other) = delete;
		PlateComponent& operator=(PlateComponent&& other) = delete;
	private:
	};
}



