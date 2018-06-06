#ifndef __INPUTCLASS_H__
#define __INPUTCLASS_H__

#define DIRECTINPUT_VERSION 0x0800
#define KEYUP(State, KeyID) (State[KeyID] == 0)
#define KEYDOWN(State, KeyID) (State[KeyID] & 0x80)
#define MOUSE_LBUTTON 0
#define MOUSE_RBUTTON 1
#define MOUSE_WBUTTON 2

#include <dinput.h>

#pragma comment (lib, "dinput8")
#pragma comment (lib, "dxguid")

class InputClass
{
public:
	InputClass();
	~InputClass();

	bool Initialize(HWND, HINSTANCE);
	void Update(HWND, float);

	int GetMouseChangeX();
	int GetMouseChangeY();
	POINT GetMouseCursorPos();
	BYTE* GetPrevMouseButtonState();
	BYTE* GetCurrMouseButtonState();

	BYTE* GetPrevKeyState();
	BYTE* GetCurrKeyState();

	bool IsKeyUp(int);
	bool IsKeyDown(int);
	bool IsMouseButtonUp(int);
	bool IsMouseButtonDown(int);

private:
	IDirectInput8* InputDevice;
	IDirectInputDevice8* KeyboardDevice;
	IDirectInputDevice8* MouseDevice;

	BYTE PrevKeyState[256];
	BYTE CurrKeyState[256];
	DIMOUSESTATE PrevMouseState;
	DIMOUSESTATE CurrMouseState;
	POINT CurrMouseCursorPos;
};

#endif