#include "InputManager.h"

using namespace Engine;

void InputManager::Update(const float& deltaTime)
{
    memcpy(&_oldKeyState, &_keyState, sizeof(_keyState));
    memcpy(&_oldMouseState, &_mouseState, sizeof(_mouseState));

    _pKeyBoard->GetDeviceState(sizeof(_keyState), &_keyState);
    _pMouse->GetDeviceState(sizeof(_mouseState), &_mouseState);

    DWORD result;    
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    result = XInputGetState(0, &state);

    memcpy(&_oldPadState, &_padState, sizeof(GamePadState));
    _padState.button = state.Gamepad.wButtons;
    
    for (int i = 0; i < GamePadState::Thumb_END; i++)
    {
        short value = *(&state.Gamepad.sThumbLX + i);
        short deadZone = i > 1 ? _rightThumbDeadZone : _leftThumbDeadZone;

        if (abs(value) < deadZone) value = 0;
        _padState.thumb[i] = ClampStickValue(value);
    }

    for (int i = 0; i < GamePadState::Trigger_END; i++)
    {
        short value = *(&state.Gamepad.bLeftTrigger + i);
        
        if (abs(value) < _triggerThreshold) value = 0;
        _padState.trigger[i] = ClampTriggerValue(*(&state.Gamepad.bLeftTrigger + i));
    }
}

bool Engine::InputManager::SetUpInputDevice(HINSTANCE hInstance, HWND hWnd)
{
    if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_pInputSDK, NULL)))
        return false;

    if (FAILED(_pInputSDK->CreateDevice(GUID_SysKeyboard, &_pKeyBoard, nullptr)))
        return false;

    if (FAILED(_pKeyBoard->SetDataFormat(&c_dfDIKeyboard)))
        return false;

    if (FAILED(_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
        return false;

    if (FAILED(_pKeyBoard->Acquire()))
        return false;

    if (FAILED(_pInputSDK->CreateDevice(GUID_SysMouse, &_pMouse, nullptr)))
        return false;

    if (FAILED(_pMouse->SetDataFormat(&c_dfDIMouse)))
        return false;

    if (FAILED(_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
        return false;

    if (FAILED(_pMouse->Acquire()))
        return false;

    return true;
}

bool Engine::InputManager::IsKeyDown(_byte keycord) const
{
    return !(_oldKeyState[keycord] & 0x80) && (_keyState[keycord] & 0x80);
}

bool Engine::InputManager::IsKeyDown(Input::MouseState mouseState) const
{
    return !(_oldMouseState.rgbButtons[mouseState] & 0x80) && (_mouseState.rgbButtons[mouseState] & 0x80);
}

bool Engine::InputManager::IsKeyDown(Input::PadState padState) const
{
    switch (padState)
    {
    case Input::PAD_LT:
        return !(_oldPadState.trigger[GamePadState::LT]) && (_padState.trigger[GamePadState::LT]);
    case Input::PAD_RT:
        return !(_oldPadState.trigger[GamePadState::RT]) && (_padState.trigger[GamePadState::RT]);
    }

    return !(_oldPadState.button & padState) && (_padState.button & padState);
}

bool Engine::InputManager::IsKeyUp(_byte keycord) const
{
    return (_oldKeyState[keycord] & 0x80) && !(_keyState[keycord] & 0x80);
}

bool Engine::InputManager::IsKeyUp(Input::MouseState mouseState) const
{
    return (_oldMouseState.rgbButtons[mouseState] & 0x80) && !(_mouseState.rgbButtons[mouseState] & 0x80);
}

bool Engine::InputManager::IsKeyUp(Input::PadState padState) const
{
    return (_oldPadState.button & padState) && !(_padState.button & padState);
}

bool Engine::InputManager::IsKeyPress(_byte keycord) const
{
    if (_keyState[keycord] & 0x80)
        return true;

    return false;
}

bool Engine::InputManager::IsKeyPress(Input::MouseState mouseState) const
{
    if (_mouseState.rgbButtons[mouseState] & 0x80)
        return true;

    return false;
}

bool Engine::InputManager::IsKeyPress(Input::PadState padState) const
{
    return _padState.button & padState;
}

float Engine::InputManager::GetAxis(Input::Axis type)
{
    float axis = 0.f;

    switch (type)
    {
    case Input::Vertical:
        axis = -_padState.thumb[GamePadState::LY];
        if (IsKeyPress(DIK_W)) axis = -1.f;
        if (IsKeyPress(DIK_S)) axis = 1.f;
        break;
    case Input::Horizontal:
        axis = _padState.thumb[GamePadState::LX];
        if (IsKeyPress(DIK_A)) axis = -1.f;
        if (IsKeyPress(DIK_D)) axis = 1.f;        
        break;
    }

    return axis;
}

bool Engine::InputManager::IsMouseWheel(Input::MouseState mouseState) const
{
    switch (mouseState)
    {
    case Input::DIM_WHDN:
        if (0 > _mouseState.lZ) return true;
        break;
    case Input::DIM_WHUP:
        if (0 < _mouseState.lZ) return true;
        break;
    }

    return false;
}

float Engine::InputManager::GetMouseMove(Input::MouseMove mouseMove) const
{
    return (float)*(&_mouseState.lX + mouseMove);
}

void Engine::InputManager::SetVibration(float power)
{
    XINPUT_VIBRATION vibration{};
    USHORT vibrationPower = static_cast<USHORT>(USHORT_MAX * power);
    vibration = { vibrationPower, vibrationPower };
    XInputSetState(0, &vibration);
}

float Engine::InputManager::ClampStickValue(short& value)
{
    return std::clamp(static_cast<float>(value), -1.f, 1.f);
}

float Engine::InputManager::ClampTriggerValue(byte& value)
{
    return std::clamp(static_cast<float>(value), 0.f, 1.f);
}

void Engine::InputManager::Free()
{
    SafeRelease(_pKeyBoard);
    SafeRelease(_pMouse);
    SafeRelease(_pInputSDK);  
}