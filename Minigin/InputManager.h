#pragma once
#include <XInput.h>

#include "Commands.h"
#include "Singleton.h"
#include <map>

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

	struct ButtonInfo
	{
		ControllerButton button;
		InputState inputState;
	};

	inline bool operator<(const ButtonInfo& lhs, const ButtonInfo& rhs)
	{
		return lhs.button < rhs.button;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(const ControllerButton& button) const;
		bool IsDown(const ControllerButton& button) const;
		bool IsReleased(const ControllerButton& button) const;
		void AddInput(const ButtonInfo& button, Command* pCommand);

	private:
		bool ProcessController();
		bool ProcessKeyBoard();
		bool HandleCommands();
		
		using ControllerCommandMap = std::map<ButtonInfo, std::unique_ptr<Command>>;
		ControllerCommandMap m_Commands{};
		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};
	};

}
