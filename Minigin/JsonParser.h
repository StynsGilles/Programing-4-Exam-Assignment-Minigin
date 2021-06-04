#pragma once
#include "string"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "iostream"

namespace dae
{
	class JsonParser
	{
	protected:
		static rapidjson::Document ReadJsonFile(std::wstring filePath)
		{
			std::cout << "reading in the level" << std::endl;
			using rapidjson::Document;
			Document jsonDoc;
			FILE* file = nullptr;

			_wfopen_s(&file, filePath.c_str(), L"rb");

			if (file != nullptr)
			{
				fseek(file, 0, SEEK_END);
				const size_t size = ftell(file);
				fseek(file, 0, SEEK_SET);
				//long current = ftell(file);
				char* readBuffer = new char[size];
				rapidjson::FileReadStream is(file, readBuffer, sizeof(readBuffer));
				jsonDoc.ParseStream(is);
				delete[] readBuffer;
				fclose(file);
				return jsonDoc;
			}
			std::cout << "file not found" << std::endl;
			return jsonDoc;
		}
	};
}
