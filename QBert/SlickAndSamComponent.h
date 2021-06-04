#pragma once
#include "EntityComponent.h"

namespace dae
{
	class LevelComponent;
	struct LevelCube;

	class SlickAndSamComponent  final : public EntityComponent
	{
	public:
		SlickAndSamComponent(LevelComponent* pPyramid, float jumpInterval);
		virtual ~SlickAndSamComponent();

		void Update() override;
		void Render() const override;

		SlickAndSamComponent(const SlickAndSamComponent& other) = delete;
		SlickAndSamComponent(SlickAndSamComponent&& other) = delete;
		SlickAndSamComponent& operator=(const SlickAndSamComponent& other) = delete;
		SlickAndSamComponent& operator=(SlickAndSamComponent&& other) = delete;

	private:
		void Jump() override;
	};
}



