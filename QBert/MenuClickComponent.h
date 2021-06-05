#pragma once
#include <ClickComponent.h>

namespace dae
{
	class MenuClickComponent final : public ClickComponent
	{
	public:
		explicit MenuClickComponent(RenderComponent* pRenderComp);
		virtual ~MenuClickComponent();

		MenuClickComponent(const MenuClickComponent& other) = delete;
		MenuClickComponent(MenuClickComponent&& other) = delete;
		MenuClickComponent& operator=(const MenuClickComponent& other) = delete;
		MenuClickComponent& operator=(MenuClickComponent&& other) = delete;
	
	private:
		void ProcessClicked() override;
	};
}