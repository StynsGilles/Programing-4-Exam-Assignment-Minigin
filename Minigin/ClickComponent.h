#pragma once
#include "BaseComponent.h"

namespace dae
{
	class RenderComponent;

	class ClickComponent: public BaseComponent
	{
	public:
		explicit ClickComponent(RenderComponent* pRenderComp);
		virtual ~ClickComponent();

		void Update() override;
		void Render() const override;
		
		ClickComponent(const ClickComponent& other) = delete;
		ClickComponent(ClickComponent&& other) = delete;
		ClickComponent& operator=(const ClickComponent& other) = delete;
		ClickComponent& operator=(ClickComponent&& other) = delete;

	protected:
		virtual void ProcessClicked() = 0;

	private:
		RenderComponent* m_pRenderComponent;
	};
}



