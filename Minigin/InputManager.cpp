#include "MiniginPCH.h"
#include "InputManager.h"

#include "GameTime.h"

using CommandMap = std::map<dae::ActionInfo, std::unique_ptr<Command>>;

bool dae::InputManager::ProcessInput()
{
	ProcessControllers();
	const bool keepPlaying = HandleKeyBoard();
	//Handle player 1 commands
	HandleCommands(m_CommandsPlayer1, m_CurrentState, m_PreviousState);
	//Handle player 2 commands
	HandleCommands(m_CommandsPlayer2, m_CurrentStatePlayer2, m_PreviousStatePlayer2);
	
	return keepPlaying;
}

void dae::InputManager::ProcessControllers()
{
	m_PreviousState = m_CurrentState;
	m_PreviousStatePlayer2 = m_CurrentStatePlayer2;
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentStatePlayer2, sizeof(XINPUT_STATE));
	DWORD dwResult{};
	dwResult = XInputGetState(0, &m_CurrentState);
	dwResult = XInputGetState(1, &m_CurrentStatePlayer2);
}

bool dae::InputManager::HandleKeyBoard()
{
	bool mouseClicked = false;
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (!HandleEvent(e, m_CommandsPlayer1))
			return false;
		
		if (!HandleEvent(e, m_CommandsPlayer2))
			return false;

		if (e.type == SDL_MOUSEBUTTONUP)
		{
			POINT mousePos{ static_cast<LONG>(e.button.x), static_cast<LONG>(e.button.y) };
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseClicked = true;
				m_MousePosition = mousePos;
				break;
			}
		}
	}

	m_MouseUp = mouseClicked;
	
	HandleKeyDown(m_CommandsPlayer1);
	HandleKeyDown(m_CommandsPlayer2);
	
	return true;
}

bool dae::InputManager::HandleEvent(const SDL_Event& e, const CommandMap& commands)
{
	if (e.type == SDL_QUIT) return false;

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		for (CommandMap::const_iterator commandIt = commands.begin(); commandIt != commands.end(); ++commandIt)
		{
			if ((*commandIt).first.KeyboardKey == e.key.keysym.scancode
				&& (*commandIt).first.InputState == InputState::Pressed
				|| (*commandIt).first.InputState == InputState::PressedAndUp)
				(*commandIt).second->Execute();
		}
	}

	if (e.type == SDL_KEYUP)
	{
		for (CommandMap::const_iterator commandIt = commands.begin(); commandIt != commands.end(); ++commandIt)
		{
			if ((*commandIt).first.KeyboardKey == e.key.keysym.scancode
				&& (*commandIt).first.InputState == InputState::Up
				|| (*commandIt).first.InputState == InputState::PressedAndUp)
				(*commandIt).second->Execute();
		}
	}
	
	return true;
}

void dae::InputManager::HandleKeyDown(const CommandMap& commands) const
{
	for (CommandMap::const_iterator commandIt = commands.begin(); commandIt != commands.end(); ++commandIt)
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
}

void dae::InputManager::HandleCommands(const CommandMap& commandMap, const XINPUT_STATE& currentState, const XINPUT_STATE& previousState) const
{
	for (CommandMap::const_iterator commandIt = commandMap.begin(); commandIt != commandMap.end(); ++commandIt)
	{
		switch ((*commandIt).first.InputState)
		{
		case InputState::Up:
			if (IsReleased((*commandIt).first.ControllerButton, currentState, previousState)) (*commandIt).second->Execute();
			break;
		case InputState::Down:
			if (IsDown((*commandIt).first.ControllerButton, currentState)) (*commandIt).second->Execute();
			break;
		case InputState::Pressed:
			if (IsPressed((*commandIt).first.ControllerButton, currentState, previousState)) (*commandIt).second->Execute();
			break;
		case InputState::PressedAndUp:
			if (IsReleased((*commandIt).first.ControllerButton, currentState, previousState) || IsPressed((*commandIt).first.ControllerButton, currentState, previousState)) (*commandIt).second->Execute();
			break;
		}
	}
}

bool dae::InputManager::IsPressed(const ControllerButton& button, const XINPUT_STATE& currentState, const XINPUT_STATE& previousState) const
{
	return currentState.Gamepad.wButtons & static_cast<WORD>(button) &&
		!(previousState.Gamepad.wButtons & static_cast<WORD>(button));
}

bool dae::InputManager::IsDown(const ControllerButton& button, const XINPUT_STATE& currentState) const
{
	return currentState.Gamepad.wButtons & static_cast<WORD>(button);
}

bool dae::InputManager::IsReleased(const ControllerButton& button, const XINPUT_STATE& currentState, const XINPUT_STATE& previousState) const
{
	return !(currentState.Gamepad.wButtons & static_cast<WORD>(button)) &&
		previousState.Gamepad.wButtons & static_cast<WORD>(button);
}

bool dae::InputManager::IsKeyDown(const SDL_Scancode& key) const
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	return pStates[key];
}

void dae::InputManager::AddInput(const int& controllerIndex, const ActionInfo& button, Command* pCommand)
{
	switch (controllerIndex)
	{
	case 0:
		m_CommandsPlayer1.insert(std::make_pair(button, pCommand));
		break;
	case 1:
		m_CommandsPlayer2.insert(std::make_pair(button, pCommand));
		break;
	default:
		break;
	}
}

std::map<dae::ActionInfo, std::unique_ptr<Command>>& dae::InputManager::GetPlayer2Commands()
{
	return m_CommandsPlayer2;
}

bool dae::InputManager::GetMouseUp() const
{
	return m_MouseUp;
}

POINT dae::InputManager::GetMousePosition() const
{
	return m_MousePosition;
}
