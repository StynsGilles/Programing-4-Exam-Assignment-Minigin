#pragma once
#include <Scene.h>

namespace dae
{
	class BaseLevelScene : public Scene
	{
	public:
		explicit BaseLevelScene(const std::string& name, const std::wstring& fileName);

		void Initialize() override;

		BaseLevelScene(const BaseLevelScene& other) = delete;
		BaseLevelScene(BaseLevelScene&& other) = delete;
		BaseLevelScene& operator=(const BaseLevelScene& other) = delete;
		BaseLevelScene& operator=(BaseLevelScene&& other) = delete;
	protected:
		std::wstring m_FileName;
	};
}