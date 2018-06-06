#ifndef __WINDOWCLASS_H__
#define __WINDOWCLASS_H__

#include <windows.h>

#pragma comment (lib, "winmm")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class WindowClass
{
public:
	bool Initialize(HINSTANCE, int);
	HWND GetWindowHandle();

private:
	HWND WindowHandle;
};

#endif