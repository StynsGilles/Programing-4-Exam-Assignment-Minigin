#pragma once
#include "EntityComponent.h"

namespace dae
{
	class LevelComponent;
	struct LevelCube;

	class SlickAndSamComponent  final : public EntityComponent
	{
	public:
		explicit SlickAndSamComponent(LevelComponent* pPyramid, float jumpInterval);
		~SlickAndSamComponent();

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



