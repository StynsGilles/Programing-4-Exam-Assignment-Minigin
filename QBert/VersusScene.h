#pragma once
#include "BaseLevelScene.h"

namespace dae
{
	class VersusScene final : public BaseLevelScene
	{
	public:
		explicit VersusScene(const std::string& name, int level);
		~VersusScene();
		
		void Initialize() override;

		VersusScene(const VersusScene& other) = delete;
		VersusScene(VersusScene&& other) = delete;
		VersusScene& operator=(const VersusScene& other) = delete;
		VersusScene& operator=(VersusScene&& other) = delete;
	};
}
