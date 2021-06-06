#pragma once
#include "GameStructs.h"
#include "JsonParser.h"

namespace dae
{
	class LevelParser final : public JsonParser
	{
	public:
		static dae::GameRules LoadLevel(const std::wstring& filePath)
		{
			auto levelFile = ReadJsonFile(filePath);
			GameRules gameRules;
			
			if (levelFile.IsObject())
			{
				using rapidjson::Value;

				if (levelFile.HasMember("gamerules") && levelFile["gamerules"].IsObject())
				{
					if (levelFile["gamerules"].HasMember("revertible"))
						gameRules.Revertible = levelFile["gamerules"]["revertible"].GetBool();
					if (levelFile["gamerules"].HasMember("textures"))
					{
						gameRules.Colors.clear();
						auto textures = levelFile["gamerules"]["textures"].GetArray();
						for (rapidjson::SizeType idx = 0; idx < textures.Size(); idx++)
						{
							auto textureObj = textures[idx].GetObjectW();
							gameRules.Colors.push_back(textureObj["color"].GetString());
						}
					}
				}
				if (levelFile.HasMember("levelData") && levelFile["levelData"].IsObject())
				{
					if (levelFile["levelData"].HasMember("pyramidSize"))
						gameRules.PyramidSize = levelFile["levelData"]["pyramidSize"].GetInt();

					if (levelFile["levelData"].HasMember("cubeWidth"))
						gameRules.CubeWidth = levelFile["levelData"]["cubeWidth"].GetFloat();

					if (levelFile["levelData"].HasMember("cubeHeight"))
						gameRules.CubeHeight = levelFile["levelData"]["cubeHeight"].GetFloat();

					if (levelFile["levelData"].HasMember("plateRows"))
					{
						gameRules.PlateRows.clear();
						const auto plateRows = levelFile["levelData"]["plateRows"].GetArray();
						for (rapidjson::SizeType idx = 0; idx < plateRows.Size(); idx++)
						{
							auto textureObj = plateRows[idx].GetObjectW();
							gameRules.PlateRows.push_back(textureObj["row"].GetInt());
						}
					}
				}
				if (levelFile.HasMember("QBertData"))
				{
					if (levelFile["QBertData"].HasMember("lives"))
						gameRules.QBertLives = levelFile["QBertData"]["lives"].GetInt();
					if (levelFile["QBertData"].HasMember("jumpCooldown"))
						gameRules.JumpCooldownQBert = levelFile["QBertData"]["jumpCooldown"].GetFloat();
				}
				if (levelFile.HasMember("SlickAndSamData"))
				{
					if (levelFile["SlickAndSamData"].HasMember("spawnInterval"))
						gameRules.SpawnIntervalSlick = levelFile["SlickAndSamData"]["spawnInterval"].GetFloat();
					if (levelFile["SlickAndSamData"].HasMember("jumpCooldown"))
						gameRules.JumpCooldownSlick = levelFile["SlickAndSamData"]["jumpCooldown"].GetFloat();
				}
				if (levelFile.HasMember("UggAndWrongwayData"))
				{
					if (levelFile["UggAndWrongwayData"].HasMember("spawnInterval"))
						gameRules.SpawnIntervalUgg = levelFile["UggAndWrongwayData"]["spawnInterval"].GetFloat();
					if (levelFile["UggAndWrongwayData"].HasMember("jumpCooldown"))
						gameRules.JumpCooldownUgg = levelFile["UggAndWrongwayData"]["jumpCooldown"].GetFloat();
				}
				if (levelFile.HasMember("CoilyData"))
				{
					if (levelFile["CoilyData"].HasMember("spawnInterval"))
						gameRules.SpawnIntervalCoily = levelFile["CoilyData"]["spawnInterval"].GetFloat();
					if (levelFile["CoilyData"].HasMember("jumpCooldown"))
						gameRules.JumpCooldownCoily = levelFile["CoilyData"]["jumpCooldown"].GetFloat();
				}
			}
			return gameRules;
		}
	};
}


