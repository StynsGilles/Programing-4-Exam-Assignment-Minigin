#pragma once
#include <BaseComponent.h>

namespace dae
{
	class LevelComponent : public BaseComponent
	{
	public:
		LevelComponent();
		virtual ~LevelComponent();

		void Update() override;
		void Render() const override;

		LevelComponent(const LevelComponent& other) = delete;
		LevelComponent(LevelComponent&& other) = delete;
		LevelComponent& operator=(const LevelComponent& other) = delete;
		LevelComponent& operator=(LevelComponent&& other) = delete;

	private:
		
	};
}