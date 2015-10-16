// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include <windows.h>
#include <tchar.h>

#define MessageWindowClass (_T("ChromeHookCLR.MessageWindowClass"))

#define WindowPosChangedMessage (_T("ChromeHookCLR.Messages.WindowPosChanged"))
#define WindowSizeChangedMessage (_T("ChromeHookCLR.Messages.WindowSizeChanged"))

HWND g_hMessageWindow = 0;

UINT g_WindowPosChanged;
UINT g_WindowSizeChanged;

void initialize();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		initialize();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


void initialize()
{
	g_WindowPosChanged = RegisterWindowMessage(WindowPosChangedMessage);
	g_WindowSizeChanged = RegisterWindowMessage(WindowSizeChangedMessage);
}

HWND getMessageWindow()
{
	auto hwnd = g_hMessageWindow;
	if (!hwnd) {
		return g_hMessageWindow = FindWindow(MessageWindowClass, nullptr);
	}
	if (!IsWindow(hwnd)) {
		return g_hMessageWindow = FindWindow(MessageWindowClass, nullptr);
	}
	return hwnd;
}

LRESULT CALLBACK CallWndRetProc(int nAction, WPARAM wParam, LPARAM lParam)
{
	if (nAction >= 0)
	{
		auto hwnd = getMessageWindow();
		if (hwnd) {
			auto cwp = reinterpret_cast<CWPRETSTRUCT*>(lParam);
			switch (cwp->message) {
			case WM_WINDOWPOSCHANGED:
				SendNotifyMessage(hwnd, g_WindowPosChanged, reinterpret_cast<WPARAM>(cwp->hwnd), cwp->lParam);
				break;
			case WM_SIZE:
				SendNotifyMessage(hwnd, g_WindowSizeChanged, reinterpret_cast<WPARAM>(cwp->hwnd), cwp->lParam);
				break;
			}
		}
	}
	return CallNextHookEx(nullptr, nAction, wParam, lParam);
}