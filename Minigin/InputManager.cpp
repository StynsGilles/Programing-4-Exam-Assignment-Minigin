#include "MiniginPCH.h"
#include "InputManager.h"
#include "Time.h"

bool dae::InputManager::ProcessInput()
{
	ProcessController();
	const bool keepPlaying = HandleKeyBoard();
	const bool keepPlayingController = HandleCommands();

	return keepPlaying && keepPlayingController;
}

void dae::InputManager::ProcessController()
{
	m_PreviousState = m_CurrentState;
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	DWORD dwResult{};
	dwResult = XInputGetState(0, &m_CurrentState);
}

bool dae::InputManager::HandleKeyBoard()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) return false;

		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			for (ControllerCommandMap::const_iterator commandIt = m_Commands.begin(); commandIt != m_Commands.end(); ++commandIt)
			{
				if ((*commandIt).first.KeyboardKey == e.key.keysym.scancode
					&& (*commandIt).first.InputState == InputState::Pressed
					|| (*commandIt).first.InputState == InputState::PressedAndUp)
					(*commandIt).second->Execute();
			}
		}

		if (e.type == SDL_KEYUP)
		{
			for (ControllerCommandMap::const_iterator commandIt = m_Commands.begin(); commandIt != m_Commands.end(); ++commandIt)
			{
				if ((*commandIt).first.KeyboardKey == e.key.keysym.scancode
					&& (*commandIt).first.InputState == InputState::Up
					|| (*commandIt).first.InputState == InputState::PressedAndUp)
					(*commandIt).second->Execute();
			}
		}
	}

	for (ControllerCommandMap::const_iterator commandIt = m_Commands.begin(); commandIt != m_Commands.end(); ++commandIt)
	{
		switch ((*commandIt).first.InputState)
		{
		case InputState::Down:
			if (IsKeyDown((*commandIt).first.KeyboardKey)) (*commandIt).second->Execute();
			break;
		default:
			break;
		}
	}
	
	return true;
}

bool dae::InputManager::HandleCommands()
{
	for (ControllerCommandMap::const_iterator commandIt = m_Commands.begin(); commandIt != m_Commands.end(); ++commandIt)
	{
		switch ((*commandIt).first.InputState)
		{
		case InputState::Up:
			if (IsReleased((*commandIt).first.ControllerButton)) (*commandIt).second->Execute();
			break;
		case InputState::Down:
			if (IsDown((*commandIt).first.ControllerButton)) (*commandIt).second->Execute();
			break;
		case InputState::Pressed:
			if (IsPressed((*commandIt).first.ControllerButton)) (*commandIt).second->Execute();
			break;
		case InputState::PressedAndUp:
			if (IsReleased((*commandIt).first.ControllerButton) || IsPressed((*commandIt).first.ControllerButton)) (*commandIt).second->Execute();
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

bool dae::InputManager::IsKeyDown(const SDL_Scancode& key) const
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	return pStates[key];
}

void dae::InputManager::AddInput(const ActionInfo& button, Command* pCommand)
{
	m_Commands.insert(std::make_pair(button, pCommand));
}
