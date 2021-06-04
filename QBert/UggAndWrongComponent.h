#pragma once
#include "EntityComponent.h"

namespace dae
{
	class LevelComponent;

	class UggAndWrongComponent final : public EntityComponent
	{
	public:
		UggAndWrongComponent(LevelComponent* pPyramid, float jumpInterval);
		virtual ~UggAndWrongComponent();

		void Update() override;
		void Render() const override;

		UggAndWrongComponent(const UggAndWrongComponent& other) = delete;
		UggAndWrongComponent(UggAndWrongComponent&& other) = delete;
		UggAndWrongComponent& operator=(const UggAndWrongComponent& other) = delete;
		UggAndWrongComponent& operator=(UggAndWrongComponent&& other) = delete;

	private:
		void Jump() override;
	};
}
