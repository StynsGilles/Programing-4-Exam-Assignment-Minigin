#pragma once
#include <BaseComponent.h>
#include <memory>
#include <string>
#include "Texture2D.h"
#pragma warning(push)
#pragma warning (disable: 4201)
#include "glm/glm.hpp"
#pragma warning(pop)

namespace dae
{
	struct LevelCube
	{
		std::shared_ptr<Texture2D> pCubeTexture;
		glm::vec3 position;
	};
	
	class LevelComponent : public BaseComponent
	{
	public:
		LevelComponent(const std::string& initialColor);
		virtual ~LevelComponent();

		void Update() override;
		void Render() const override;

		LevelComponent(const LevelComponent& other) = delete;
		LevelComponent(LevelComponent&& other) = delete;
		LevelComponent& operator=(const LevelComponent& other) = delete;
		LevelComponent& operator=(LevelComponent&& other) = delete;

	private:
		static const int m_PyramidSize = 7;
		LevelCube* m_Pyramid[m_PyramidSize][m_PyramidSize];
	};
}
