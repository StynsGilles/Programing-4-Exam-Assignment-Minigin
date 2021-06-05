#pragma once
#include "BaseLevelScene.h"

namespace dae
{
	class CoopScene final : public BaseLevelScene
	{
	public:
		explicit CoopScene(const std::string& name, const std::wstring& fileName);

		void Initialize() override;

		CoopScene(const CoopScene& other) = delete;
		CoopScene(CoopScene&& other) = delete;
		CoopScene& operator=(const CoopScene& other) = delete;
		CoopScene& operator=(CoopScene&& other) = delete;
	};
}
