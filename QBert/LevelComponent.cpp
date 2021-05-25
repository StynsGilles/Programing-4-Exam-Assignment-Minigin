#include "LevelComponent.h"

#include <SDL_rect.h>
#include <SDL_render.h>


#include "Renderer.h"
#include "ResourceManager.h"

dae::LevelComponent::LevelComponent(const std::string& initialColor)
{
	glm::vec3 initialCubePos = glm::vec3(320, 100, 0);
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		for (int col = 0; col<= row; ++col)
		{
			LevelCube* newCube = new LevelCube();
			newCube->pCubeTexture = ResourceManager::GetInstance().LoadTexture("Cube_" + initialColor + ".png");
			SDL_Rect dst;
			SDL_QueryTexture(newCube->pCubeTexture->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
			newCube->position = initialCubePos;
			m_Pyramid[row][col] = newCube;
			if (col == row)
			{
				initialCubePos.x -= (float)dst.w / 2.f + (float)dst.w * col;
				initialCubePos.y += dst.h * 0.75f;
			}
			else
				initialCubePos.x += (float)dst.w;
		}
	}
}

dae::LevelComponent::~LevelComponent()
{
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		for (int col = 0; col <= row; ++col)
		{
			if (m_Pyramid[row][col])
				delete m_Pyramid[row][col];
		}
	}
}

void dae::LevelComponent::Update()
{
}

void dae::LevelComponent::Render() const
{
	for (int row = 0; row < m_PyramidSize; ++row)
	{
		for (int col = 0; col <= row; ++col)
		{
			if (m_Pyramid[row][col]->pCubeTexture)
				Renderer::GetInstance().RenderTexture(*m_Pyramid[row][col]->pCubeTexture, m_Pyramid[row][col]->position.x, m_Pyramid[row][col]->position.y);
		}
	}
}
