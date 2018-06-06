#include "WindowClass.h"
#include "resource.h"

bool WindowClass :: Initialize(HINSTANCE hinstance, int show)
{
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	wndClass.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON1));
	wndClass.hInstance = hinstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = L"Cube";
	wndClass.lpszMenuName = 0;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClass(&wndClass))
	{
		MessageBox(0, L"WindowClass.cpp - RegisterClass() Failed", 0, 0);
		
		return false;
	}

	WindowHandle = CreateWindow(wndClass.lpszClassName, wndClass.lpszClassName, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, (HMENU)NULL, hinstance, NULL);
	if(WindowHandle == 0)
	{
		MessageBox(0, L"WindowClass.cpp - CreateWindow() Failed", 0, 0);

		return false;
	}

	ShowWindow(WindowHandle, show);
	UpdateWindow(WindowHandle);

	return true;
}

HWND WindowClass :: GetWindowHandle()
{
	return WindowHandle;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT imessage, WPARAM wparam, LPARAM lparam)
{
	switch(imessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,imessage,wparam,lparam);
}