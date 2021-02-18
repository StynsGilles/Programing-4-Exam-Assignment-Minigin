#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

#include "Time.h"

bool dae::InputManager::ProcessInput()
{	
	ProcessController();
	const bool keepPlaying= ProcessKeyBoard();
	HandleCommands();
	
	return keepPlaying;
}

bool dae::InputManager::ProcessController()
{
	m_PreviousState = m_CurrentState;
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	DWORD dwResult{};
	dwResult = XInputGetState(0, &m_CurrentState);
	if (dwResult != ERROR_SUCCESS)
	{
		std::cout << "No controller connected!" << std::endl;
	}

	return true;
}

bool dae::InputManager::ProcessKeyBoard()
{	
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

bool dae::InputManager::HandleCommands()
{
	for (ControllerCommandMap::const_iterator commandIt = m_Commands.begin(); commandIt != m_Commands.end(); ++commandIt)
	{
		switch ((*commandIt).first.inputState)
		{
		case InputState::Up:
			if (IsReleased((*commandIt).first.button)) (*commandIt).second->Execute();
			break;
		case InputState::Down:
			if (IsDown((*commandIt).first.button)) (*commandIt).second->Execute();
			break;
		case InputState::Pressed:
			if (IsPressed((*commandIt).first.button)) (*commandIt).second->Execute();
			break;
		case InputState::PressedAndUp:
			if (IsReleased((*commandIt).first.button) || IsPressed((*commandIt).first.button)) (*commandIt).second->Execute();
			break;
		}
	}

	return true;
}

bool dae::InputManager::IsPressed(const ControllerButton& button) const
{
	return m_CurrentState.Gamepad.wButtons & static_cast<WORD>(button) &&
		!(m_PreviousState.Gamepad.wButtons & static_cast<WORD>(button));
}

bool dae::InputManager::IsDown(const ControllerButton& button) const
{
	return m_CurrentState.Gamepad.wButtons & static_cast<WORD>(button);
}

bool dae::InputManager::IsReleased(const ControllerButton& button) const
{
	return !(m_CurrentState.Gamepad.wButtons & static_cast<WORD>(button)) &&
		m_PreviousState.Gamepad.wButtons & static_cast<WORD>(button);
}

void dae::InputManager::AddInput(const ButtonInfo& button, Command* pCommand)
{
	m_Commands.insert(std::make_pair(button, pCommand));
}