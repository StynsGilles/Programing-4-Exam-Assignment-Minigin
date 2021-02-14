#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

#include "Time.h"


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.scancode)
			{
			case SDL_SCANCODE_KP_1:
				Time::GetInstance().SetMsPerFrame(6);
				break;
			case SDL_SCANCODE_KP_2:
				Time::GetInstance().SetMsPerFrame(16);
				break;
			case SDL_SCANCODE_KP_3:
				Time::GetInstance().SetMsPerFrame(33);
				break;
			default:
				break;
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

