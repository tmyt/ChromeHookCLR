#include "stdafx.h"

#ifdef _WIN64
#define WND_CLASS (_T("ChromeHook.InjectDLL64.Class"))
#else
#define WND_CLASS (_T("ChromeHook.InjectDLL32.Class"))
#endif

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

// hook vars
HMODULE g_hookDll;
HHOOK g_hcwpHook;
HHOOK g_hgmHook;
HOOKPROC g_cwpHookProc;
HOOKPROC g_gmHookProc;

void installHook();
void uninstallHook();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex = {0};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = WND_CLASS;
	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd = CreateWindowW(WND_CLASS, nullptr, 0, 
		0, 0, 0, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		installHook();
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		uninstallHook();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void installHook()
{
	// install hook
#ifdef _WIN64
	g_hookDll = LoadLibrary(_T("ChromeHook64.dll"));
#else
	g_hookDll = LoadLibrary(_T("ChromeHook32.dll"));
#endif
	g_cwpHookProc = (HOOKPROC) GetProcAddress(g_hookDll, "CallWndRetProc");
	g_gmHookProc = (HOOKPROC)GetProcAddress(g_hookDll, "GetMsgProc");
	g_hcwpHook = SetWindowsHookEx(WH_CALLWNDPROCRET, g_cwpHookProc, g_hookDll, 0);
	g_hgmHook = SetWindowsHookEx(WH_CALLWNDPROCRET, g_gmHookProc, g_hookDll, 0);
	Sleep(10); // wait 10ms
	PostMessage(HWND_BROADCAST, WM_NULL, 0, 0);
}

void uninstallHook()
{
	// unhook installed hook
	UnhookWindowsHookEx(g_hcwpHook);
	UnhookWindowsHookEx(g_hgmHook);
	Sleep(10);
	PostMessage(HWND_BROADCAST, WM_NULL, 0, 0);
	FreeLibrary(g_hookDll);
	g_hookDll = nullptr;
}