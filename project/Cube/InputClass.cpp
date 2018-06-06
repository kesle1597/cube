#include "InputClass.h"

InputClass :: InputClass()
{
	InputDevice = 0;
	KeyboardDevice = 0;
	MouseDevice = 0;
}

InputClass :: ~InputClass()
{
	if(InputDevice != 0)
	{
		InputDevice -> Release();
		InputDevice = 0;
	}

	if(KeyboardDevice != 0)
	{
		KeyboardDevice -> Release();
		KeyboardDevice = 0;
	}

	if(MouseDevice != 0)
	{
		MouseDevice -> Release();
		MouseDevice = 0;
	}
}

bool InputClass :: Initialize(HWND hwnd, HINSTANCE hinstance)
{
	HRESULT hr;
	
	hr = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&InputDevice, 0);
	if(FAILED(hr))
	{
		MessageBox(0, L"InputClass.cpp - Initialize() Failed", 0, 0);

		return false;
	}

	hr = InputDevice -> CreateDevice(GUID_SysKeyboard, &KeyboardDevice, 0);
	if(FAILED(hr))
	{
		MessageBox(0, L"InputClass.cpp - CreateDevice() Failed", 0, 0);

		return false;
	}

	hr = KeyboardDevice -> SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(0, L"InputClass.cpp - SetDataFormat() Failed", 0, 0);
	}

	hr = KeyboardDevice -> SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if(FAILED(hr))
	{
		MessageBox(0, L"InputClass.cpp - SetCooperativeLevel() Failed", 0, 0);

		return false;
	}

	hr = InputDevice -> CreateDevice(GUID_SysMouse, &MouseDevice, 0);
	if(FAILED(hr))
	{
		MessageBox(0, L"InputClass.cpp - CreateDevice() Failed", 0, 0);

		return false;
	}

	hr = MouseDevice -> SetDataFormat(&c_dfDIMouse);
	if(FAILED(hr))
	{
		MessageBox(0, L"InputClass.cpp - SetDateFormat() Failed", 0, 0);

		return false;
	}

	hr = MouseDevice -> SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if(FAILED(hr))
	{
		MessageBox(0, L"InputClass.cpp - SetCooperativeLevel() Failed", 0, 0);

		return false;
	}

	if(FAILED(KeyboardDevice -> GetDeviceState(sizeof(CurrKeyState), &CurrKeyState)))
	{
		if(FAILED(KeyboardDevice -> Acquire()))
		{
			return false;
		}
		else
		{
			KeyboardDevice -> GetDeviceState(sizeof(CurrKeyState), &CurrKeyState);
		}
	}

	if(FAILED(MouseDevice -> GetDeviceState(sizeof(DIMOUSESTATE), &CurrMouseState)))
	{
		if(FAILED(MouseDevice -> Acquire()))
		{
			return false;
		}
		else
		{
			MouseDevice -> GetDeviceState(sizeof(DIMOUSESTATE), &CurrMouseState);
		}
	}

	return true;
}

void InputClass :: Update(HWND hwnd, float timeDelta)
{
	for(int i = 0; i < 256; i++)
	{
		PrevKeyState[i] = CurrKeyState[i];
	}

	if(FAILED(KeyboardDevice -> GetDeviceState(sizeof(CurrKeyState), &CurrKeyState)))
	{
		if(FAILED(KeyboardDevice -> Acquire()))
		{
			return;
		}
		else
		{
			KeyboardDevice -> GetDeviceState(sizeof(CurrKeyState), &CurrKeyState);
		}
	}

	PrevMouseState = CurrMouseState;

	if(FAILED(MouseDevice -> GetDeviceState(sizeof(DIMOUSESTATE), &CurrMouseState)))
	{
		if(FAILED(MouseDevice -> Acquire()))
		{
			return;
		}
		else
		{
			MouseDevice -> GetDeviceState(sizeof(DIMOUSESTATE), &CurrMouseState);
		}
	}

	GetCursorPos(&CurrMouseCursorPos);
	ScreenToClient(hwnd, &CurrMouseCursorPos);
}

int InputClass :: GetMouseChangeX()
{
	return (int)CurrMouseState.lX;
}

int InputClass :: GetMouseChangeY()
{
	return (int)CurrMouseState.lY;
}

BYTE* InputClass :: GetPrevKeyState()
{
	return PrevKeyState;
}

BYTE* InputClass :: GetCurrKeyState()
{
	return CurrKeyState;
}

BYTE* InputClass :: GetPrevMouseButtonState()
{
	return PrevMouseState.rgbButtons;
}

BYTE* InputClass :: GetCurrMouseButtonState()
{
	return CurrMouseState.rgbButtons;
}

POINT InputClass :: GetMouseCursorPos()
{
	return CurrMouseCursorPos;
}

bool InputClass :: IsKeyUp(int key)
{
	if(KEYDOWN(PrevKeyState, key) && KEYUP(CurrKeyState, key))
		return true;
	
	return false;
}

bool InputClass :: IsKeyDown(int key)
{
	if(KEYUP(PrevKeyState, key) && KEYDOWN(CurrKeyState, key))
		return true;

	return false;
}

bool InputClass :: IsMouseButtonUp(int key)
{
	if(KEYDOWN(PrevMouseState.rgbButtons, key) && KEYUP(CurrMouseState.rgbButtons, key))
		return true;

	return false;
}

bool InputClass :: IsMouseButtonDown(int key)
{
	if(KEYUP(PrevMouseState.rgbButtons, key) && KEYUP(CurrMouseState.rgbButtons, key))
		return true;

	return false;
}