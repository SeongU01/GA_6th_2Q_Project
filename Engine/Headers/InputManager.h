#pragma once

#include "Base.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

namespace Input
{
	enum MouseState { DIM_LB, DIM_RB, DIM_WM, DIM_END, DIM_WHUP = 120, DIM_WHDN = -120 };
	enum MouseMove { DIM_X, DIM_Y };
	enum PadState
	{
		PAD_UP = XINPUT_GAMEPAD_DPAD_UP,
		PAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		PAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
		PAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
		PAD_LS = XINPUT_GAMEPAD_LEFT_THUMB,
		PAD_RS = XINPUT_GAMEPAD_RIGHT_THUMB,
		PAD_LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
		PAD_RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		PAD_A = XINPUT_GAMEPAD_A,
		PAD_B = XINPUT_GAMEPAD_B,
		PAD_X = XINPUT_GAMEPAD_X,
		PAD_Y = XINPUT_GAMEPAD_Y,
		PAD_LT = 0x10000,
		PAD_RT = 0x20000
	};
	enum Axis { Vertical, Horizontal };
}

namespace Engine
{
	class InputManager : public Base, public SingleTon<InputManager>
	{
		friend class SingleTon;
	private:
		struct ButtonQueue
		{
			ButtonQueue(unsigned short old, unsigned short curr)
				: old(old), curr(curr), elapsed(0.f) {}
			unsigned short old;
			unsigned short curr;
			float elapsed;
		};
	public:
		enum PadType { Thumb, Trigger };
		struct GamePadState
		{
			enum Thumb { LX, LY, RX, RY, Thumb_END };
			enum Trigger { LT, RT, Trigger_END };
			float thumb[Thumb_END];
			float trigger[Trigger_END];
			unsigned short button;
		};
	private:
		enum class InputType { KeyBoardnMouse, GamePad };
	private:
		explicit InputManager() = default;
		virtual ~InputManager() = default;
		NOCOPY(InputManager)

	public:
		void Update(const float& deltaTime);
		bool SetUpInputDevice(HINSTANCE hInstance, HWND hWnd);
		
	public:
		bool IsKeyDown(_byte keycord) const;
		bool IsKeyDown(Input::MouseState mouseState) const;
		bool IsKeyDown(Input::PadState padState) const;
		bool IsKeyUp(_byte keycord) const;
		bool IsKeyUp(Input::MouseState mouseState) const;
		bool IsKeyUp(Input::PadState padState) const;
		bool IsKeyPress(_byte keycord) const;
		bool IsKeyPress(Input::MouseState mouseState) const;
		bool IsKeyPress(Input::PadState padState) const;
		float GetAxis(Input::Axis type);
		bool IsMouseWheel(Input::MouseState mouseState) const;
		float GetMouseMove(Input::MouseMove mouseMove) const;
		void SetThumbDeadZone(short left, short right) { _leftThumbDeadZone = left; _rightThumbDeadZone = right; }
		void SetTriggerThreshold(byte value) { _triggerThreshold = value; }
		void SetVibration(float power);

	private:
		float ClampStickValue(short& value);
		float ClampTriggerValue(byte& value);

	private:
		void Free() override;

	private:
		_byte						_oldKeyState[256]{};
		_byte						_keyState[256]{};
		DIMOUSESTATE				_oldMouseState{};
		DIMOUSESTATE				_mouseState{};
		GamePadState				_oldPadState{};
		GamePadState				_padState{};

		LPDIRECTINPUT8				_pInputSDK = nullptr;
		LPDIRECTINPUTDEVICE8		_pKeyBoard = nullptr;
		LPDIRECTINPUTDEVICE8		_pMouse = nullptr;

		short						_leftThumbDeadZone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		short						_rightThumbDeadZone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		byte						_triggerThreshold = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		InputType					_currInputType{};
	};
}