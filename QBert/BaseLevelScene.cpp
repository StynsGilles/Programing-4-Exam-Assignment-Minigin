#include "pch.h"
#include "BaseLevelScene.h"

dae::BaseLevelScene::BaseLevelScene(const std::string& name, const std::wstring& fileName)
	: Scene(name)
	, m_FileName(fileName)
{
}

void dae::BaseLevelScene::Initialize()
{
}
