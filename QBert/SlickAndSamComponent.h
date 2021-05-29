#pragma once
#include <BaseComponent.h>

namespace dae
{
	class LevelComponent;
	struct LevelCube;

	class SlickAndSamComponent final : public BaseComponent
	{
	public:
		SlickAndSamComponent(LevelComponent* pPyramid);
		virtual ~SlickAndSamComponent();

		void Update() override;
		void Render() const override;
		void ChangeCube(LevelCube* pNewCube);
		LevelCube* GetCurrentCube() const;

		SlickAndSamComponent(const SlickAndSamComponent& other) = delete;
		SlickAndSamComponent(SlickAndSamComponent&& other) = delete;
		SlickAndSamComponent& operator=(const SlickAndSamComponent& other) = delete;
		SlickAndSamComponent& operator=(SlickAndSamComponent&& other) = delete;

	private:
		LevelComponent* m_pPyramid = nullptr;
		LevelCube* m_pCurrentCube = nullptr;

		const float m_JumpInterval = 2.f;
		float m_JumpTimer = 0.f;

		void Jump();
		void UpdatePosition(const glm::vec3& nextPosition);
	};
}



