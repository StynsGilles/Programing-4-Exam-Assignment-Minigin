#pragma once
#include "CoilyNPCComponent.h"

namespace dae
{
	class CoilyPlayerComponent : public CoilyNPCComponent
	{
	public:
		CoilyPlayerComponent(LevelComponent* pPyramid, float jumpInterval);
		virtual ~CoilyPlayerComponent();

		CoilyPlayerComponent(const CoilyPlayerComponent& other) = delete;
		CoilyPlayerComponent(CoilyPlayerComponent&& other) = delete;
		CoilyPlayerComponent& operator=(const CoilyPlayerComponent& other) = delete;
		CoilyPlayerComponent& operator=(CoilyPlayerComponent&& other) = delete;

	private:
		bool m_CanJump = true;
		
		void ChasePlayer() override;
	};
}