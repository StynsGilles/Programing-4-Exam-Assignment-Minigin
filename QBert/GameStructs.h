#pragma once
#include "pch.h"

namespace dae
{
	class Texture2D;

	struct GameRules
	{
		//gamerules
		bool Revertible = false;
		std::vector<std::string> Colors{ "Pink", "Yellow" };
		//levelData
		int PyramidSize = 7;
		float CubeWidth = 64.f;
		float CubeHeight = 64.f;
		std::vector<int> PlateRows{ 3 };
		//QBertData
		int QBertLives = 3;
		float JumpCooldownQBert = 0.5f;
		//SlickAndSamData
		float SpawnIntervalSlick = 10.f;
		float JumpCooldownSlick = 1.f;
		//UggAndWrongwayData
		float SpawnIntervalUgg = 10.f;
		float JumpCooldownUgg = 1.f;
		//CoilyData
		float SpawnIntervalCoily = 10.f;
		float JumpCooldownCoily = 1.f;
	};

	struct LevelCube
	{
		std::vector<std::shared_ptr<Texture2D>> pCubeTextures;
		glm::vec3 position;
		int stage = 0;
		bool reversible = false;
		GameObject* entity = nullptr;
	};

	enum class Side
	{
		left,
		right
	};

	enum class CoilyState
	{
		egg,
		normal,
		targettedPlate
	};

	enum class EnemyType
	{
		top,
		left,
		right
	};
}