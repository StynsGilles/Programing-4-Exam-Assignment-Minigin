#pragma once
#include <XInput.h>
#include "Commands.h"
#include "Singleton.h"
#include <map>
#include <SDL.h>

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		Up = XINPUT_GAMEPAD_DPAD_UP,
		Down = XINPUT_GAMEPAD_DPAD_DOWN,
		Left = XINPUT_GAMEPAD_DPAD_LEFT,
		Right = XINPUT_GAMEPAD_DPAD_RIGHT,
		LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK
	};

	enum class InputState
	{
		Pressed,
		Up,
		PressedAndUp,
		Down
	};
	
	struct ActionInfo
	{
		ActionInfo(const ControllerButton& cButton, const SDL_Scancode& key, const InputState& state)
			: ControllerButton(cButton)
			, KeyboardKey(key)
			, InputState(state)
		{}
		
		ControllerButton ControllerButton;
		SDL_Scancode KeyboardKey;
		InputState InputState;
	};

	inline bool operator<(const ActionInfo& lhs, const ActionInfo& rhs)
	{
		return lhs.ControllerButton < rhs.ControllerButton;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(const ControllerButton& button) const;
		bool IsDown(const ControllerButton& button) const;
		bool IsReleased(const ControllerButton& button) const;
		bool IsKeyDown(const SDL_Scancode& key) const;
		void AddInput(const int& controllerIndex, const ActionInfo& button, Command* pCommand);

	private:
		void ProcessControllers();
		bool HandleKeyBoard();
		using CommandMap = std::map<ActionInfo, std::unique_ptr<Command>>;
		void HandleCommands(const CommandMap& commandMap);

		CommandMap m_CommandsPlayer1{};
		CommandMap m_CommandsPlayer2{};
		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};
		XINPUT_STATE m_PreviousStatePlayer2{};
		XINPUT_STATE m_CurrentStatePlayer2{};
	};
}
