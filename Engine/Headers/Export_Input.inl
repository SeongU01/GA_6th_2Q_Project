#pragma once

bool IsKeyDown(_byte keycord)
{
	return Engine::InputManager::GetInstance()->IsKeyDown(keycord);
}
bool IsKeyDown(Input::MouseState mouseState)
{
	return Engine::InputManager::GetInstance()->IsKeyDown(mouseState);
}
bool IsKeyDown(Input::PadState padState)
{
	return Engine::InputManager::GetInstance()->IsKeyDown(padState);
}
bool IsKeyUp(_byte keycord)
{
	return Engine::InputManager::GetInstance()->IsKeyUp(keycord);
}
bool IsKeyUp(Input::MouseState mouseState)
{
	return Engine::InputManager::GetInstance()->IsKeyUp(mouseState);
}
bool IsKeyUp(Input::PadState padState)
{
	return Engine::InputManager::GetInstance()->IsKeyUp(padState);
}
bool IsKeyPress(_byte keycord)
{
	return Engine::InputManager::GetInstance()->IsKeyPress(keycord);
}
bool IsKeyPress(Input::MouseState mouseState)
{
	return Engine::InputManager::GetInstance()->IsKeyPress(mouseState);
}
bool IsKeyPress(Input::PadState padState)
{
	return Engine::InputManager::GetInstance()->IsKeyPress(padState);
}
float GetAxis(Input::Axis type)
{
	return Engine::InputManager::GetInstance()->GetAxis(type);
}
float GetMouseMove(Input::MouseMove mouseMove)
{
	return Engine::InputManager::GetInstance()->GetMouseMove(mouseMove);
}
bool IsMouseWheel(Input::MouseState mouseState)
{
	Engine::InputManager::GetInstance()->IsMouseWheel(mouseState);
}
void SetThumbDeadZone(short left, short right)
{
	Engine::InputManager::GetInstance()->SetThumbDeadZone(left, right);
}
void SetTriggerThreshold(byte value)
{
	Engine::InputManager::GetInstance()->SetTriggerThreshold(value);
}
void SetVibration(float power)
{
	Engine::InputManager::GetInstance()->SetVibration(power);
}