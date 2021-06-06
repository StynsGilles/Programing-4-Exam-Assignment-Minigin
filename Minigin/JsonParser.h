#pragma once
#include <document.h>
#include <filereadstream.h>
#include <rapidjson.h>

#include "iostream"
#include "string"

namespace dae
{
	class JsonParser
	{
	protected:
		static rapidjson::Document ReadJsonFile(const std::wstring& filePath)
		{
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
			return jsonDoc;
		}
	};
}
