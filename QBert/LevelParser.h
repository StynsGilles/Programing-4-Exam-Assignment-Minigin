#pragma once
#include "JsonParser.h"

namespace dae
{
	class LevelParser : dae::JsonParser
	{
	public:
		static void LoadLevel(std::wstring filePath, 
			bool& revertible, std::vector<std::string>& colors, 
			int& pyramidSize, std::vector<int>& plateRowsVector, 
			int& qbertLives, float& qbertJumpCD,
			float& spawnIntervalSlick, float& jumpCdSlick, 
			float& spawnIntervalUgg, float& jumpCdUgg,
			float& spawnIntervalCoily, float& jumpCdCoily)
		{
			auto levelFile = ReadJsonFile(filePath);

			using rapidjson::Value;
			
			if (levelFile.HasMember("gamerules") && levelFile["gamerules"].IsObject())
			{
				if (levelFile["gamerules"].HasMember("revertible"))
				{
					revertible = levelFile["gamerules"]["revertible"].GetBool();
					
					std::cout << "file has data for revertible, revertible is: "<<revertible << std::endl;
				}
				if (levelFile["gamerules"].HasMember("textures"))
				{
					colors.clear();
					auto textures = levelFile["gamerules"]["textures"].GetArray();
					for (rapidjson::SizeType idx = 0; idx < textures.Size(); idx++)
					{
						auto textureObj= textures[idx].GetObjectW();
						std::cout << textureObj["color"].GetString() << std::endl;
						colors.push_back(textureObj["color"].GetString());
					}
				}
			}
			if (levelFile.HasMember("levelData") && levelFile["levelData"].IsObject())
			{
				if (levelFile["levelData"].HasMember("pyramidSize"))
				{
					pyramidSize = levelFile["levelData"]["pyramidSize"].GetInt();
					std::cout << "pyramidsize:" << pyramidSize << std::endl;
				}
				if (levelFile["levelData"].HasMember("plateRows"))
				{
					plateRowsVector.clear();
					auto plateRows = levelFile["levelData"]["plateRows"].GetArray();
					for (rapidjson::SizeType idx = 0; idx < plateRows.Size(); idx++)
					{
						auto textureObj = plateRows[idx].GetObjectW();
						std::cout << textureObj["row"].GetInt() << std::endl;
						plateRowsVector.push_back(textureObj["row"].GetInt());
					}
				}
			}
			if (levelFile.HasMember("QBertData"))
			{
				if (levelFile["QBertData"].HasMember("lives"))
					qbertLives = levelFile["QBertData"]["lives"].GetInt();
				if (levelFile["QBertData"].HasMember("jumpCooldown"))
					qbertJumpCD = levelFile["QBertData"]["jumpCooldown"].GetFloat();
			}
			if (levelFile.HasMember("SlickAndSamData"))
			{
				if (levelFile["SlickAndSamData"].HasMember("spawnInterval"))
					spawnIntervalSlick = levelFile["SlickAndSamData"]["spawnInterval"].GetFloat();
				if (levelFile["SlickAndSamData"].HasMember("jumpCooldown"))
					jumpCdSlick = levelFile["SlickAndSamData"]["jumpCooldown"].GetFloat();
			}
			if (levelFile.HasMember("UggAndWrongwayData"))
			{
				if (levelFile["UggAndWrongwayData"].HasMember("spawnInterval"))
					spawnIntervalUgg = levelFile["UggAndWrongwayData"]["spawnInterval"].GetFloat();
				if (levelFile["UggAndWrongwayData"].HasMember("jumpCooldown"))
					jumpCdUgg = levelFile["UggAndWrongwayData"]["jumpCooldown"].GetFloat();
			}
			if (levelFile.HasMember("CoilyData"))
			{
				if (levelFile["CoilyData"].HasMember("spawnInterval"))
					spawnIntervalCoily = levelFile["CoilyData"]["spawnInterval"].GetFloat();
				if (levelFile["CoilyData"].HasMember("jumpCooldown"))
					jumpCdCoily = levelFile["CoilyData"]["jumpCooldown"].GetFloat();
			}
		}
	};
}


