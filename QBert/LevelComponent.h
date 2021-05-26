#pragma once
#include <BaseComponent.h>
#include <memory>
#include <string>
#include "Texture2D.h"
#pragma warning(push)
#pragma warning (disable: 4201)
#include <vector>

#include "glm/glm.hpp"
#pragma warning(pop)

namespace dae
{
	struct LevelCube
	{
		std::vector<std::shared_ptr<Texture2D>> pCubeTextures;
		glm::vec3 position;
		int stage = 0;
		bool reversible = false;
	};
	
	class LevelComponent : public BaseComponent
	{
	public:
		LevelComponent(const std::string& initialColor, const std::string& finalColor, const std::string& interColor = "", bool reversible = false);
		LevelComponent(const std::string& initialColor, const std::string& finalColor, bool reversible);
		virtual ~LevelComponent();

		void Update() override;
		void Render() const override;
		LevelCube* GetTopCube() const;
		int GetPyramidSize() const;
		LevelCube* GetNextCube(LevelCube* pCurrentCube, int rowChange, int colChange,
			bool& fellOfPyramid, bool& positiveChange);

		LevelComponent(const LevelComponent& other) = delete;
		LevelComponent(LevelComponent&& other) = delete;
		LevelComponent& operator=(const LevelComponent& other) = delete;
		LevelComponent& operator=(LevelComponent&& other) = delete;

	private:
		static const int m_PyramidSize = 7;
		LevelCube* m_Pyramid[m_PyramidSize][m_PyramidSize];
		bool m_LevelFinished = false;
		
		bool UpdateCubeColor(LevelCube* m_pCube);
		void CheckLevelFinished();
	};
}
