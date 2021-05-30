#pragma once
#include <BaseComponent.h>

namespace dae
{
	class LevelComponent;

	class UggAndWrongComponent final : public BaseComponent
	{
	public:
		UggAndWrongComponent(LevelComponent* pPyramid);
		virtual ~UggAndWrongComponent();

		void Update() override;
		void Render() const override;

		UggAndWrongComponent(const UggAndWrongComponent& other) = delete;
		UggAndWrongComponent(UggAndWrongComponent&& other) = delete;
		UggAndWrongComponent& operator=(const UggAndWrongComponent& other) = delete;
		UggAndWrongComponent& operator=(UggAndWrongComponent&& other) = delete;

	private:
		LevelComponent* m_pPyramid = nullptr;

		const float m_JumpInterval = 2.f;
		float m_JumpTimer = 0.f;

		void Jump();
	};
}