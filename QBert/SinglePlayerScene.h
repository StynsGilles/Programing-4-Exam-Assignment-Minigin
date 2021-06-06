#pragma once
#include "BaseLevelScene.h"

namespace dae
{
	class SinglePlayerScene final : public BaseLevelScene
	{
	public:
		explicit SinglePlayerScene(const std::string& name, int level);
		
		void Initialize() override;
		
		SinglePlayerScene(const SinglePlayerScene& other) = delete;
		SinglePlayerScene(SinglePlayerScene&& other) = delete;
		SinglePlayerScene& operator=(const SinglePlayerScene& other) = delete;
		SinglePlayerScene& operator=(SinglePlayerScene&& other) = delete;
	};
}



