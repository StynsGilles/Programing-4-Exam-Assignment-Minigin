#pragma once
#include <BaseComponent.h>

namespace dae
{
	class LevelComponent;

	class EntityComponent : public BaseComponent
    {
	public:
		EntityComponent(LevelComponent* pPyramid);
		virtual ~EntityComponent();

		virtual void Update() override = 0;
		virtual void Render() const override = 0;

		static void Spawn();
		
		EntityComponent(const EntityComponent& other) = delete;
		EntityComponent(EntityComponent&& other) = delete;
		EntityComponent& operator=(const EntityComponent& other) = delete;
		EntityComponent& operator=(EntityComponent&& other) = delete;
	protected:
		LevelComponent* m_pPyramid = nullptr;

		float m_JumpInterval = 2.f;
		float m_JumpTimer = 0.f;

		void JumpUpdate();
		virtual void Jump() = 0;
		void JumpRandomDownwards(bool isSlickOrSam = false);
		void SetJumpRate(float jumpInterval);
    };
}