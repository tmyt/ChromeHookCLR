#include "Stdafx.h"
#include "MessageWindow.h"

#include <windows.h>

// TODO: Move to project settings
#pragma comment(lib, "user32.lib")

using namespace ChromeHookCLR;

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;

HINSTANCE getManagedInstanceHandle();

#pragma unmanaged

bool MessageWindow::initialized;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

MessageWindow::MessageWindow() :
	windowPosChanged(0),
	windowSizeChanged(0),
	hwnd(0),
	callback(0)
{

}

void MessageWindow::initialize()
{
	if (initialized)return;
	initialized = true;
	registerClass();
	registerMessage();
}

void MessageWindow::registerClass()
{
	WNDCLASSEX ws = { 0 };
	ws.cbSize = sizeof(ws);
	ws.cbWndExtra = sizeof(intptr_t);
	ws.lpszClassName = MessageWindowClass;
	ws.hInstance = getManagedInstanceHandle();
	ws.lpfnWndProc = WndProc;
	RegisterClassEx(&ws);
}

void MessageWindow::registerMessage()
{
	windowPosChanged = RegisterWindowMessage(WindowPosChangedMessage);
	windowSizeChanged = RegisterWindowMessage(WindowSizeChangedMessage);
	windowStateChanged = RegisterWindowMessage(WindowStateChangedMessage);
	windowDestroyed = RegisterWindowMessage(WindowDestroyedMessage);
}

void MessageWindow::createWindow()
{
	initialize();
	hwnd = CreateWindow(MessageWindowClass, nullptr, 0, 0, 0, 0, 0, nullptr, nullptr, getManagedInstanceHandle(), (LPVOID)this);
}

void MessageWindow::close()
{
	SendMessage(hwnd, WM_CLOSE, 0, 0);
	hwnd = nullptr;
}

void MessageWindow::setCallback(NativeMessageCallbackType cb)
{
	callback = cb;
}

void MessageWindow::handleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (!callback) return;
	if (msg == windowPosChanged)
	{
		callback(MessageType::Moved, wp, lp);
	}
	else if (msg == windowSizeChanged)
	{
		callback(MessageType::Size, wp, lp);
	}else if(msg == windowStateChanged)
	{
		callback(MessageType::State, wp, lp);
	}else if(msg == windowDestroyed)
	{
		callback(MessageType::Closed, wp, lp);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	auto wnd = (MessageWindow*) GetWindowLongPtr(hwnd, 0);
	switch (msg)
	{
	case WM_CREATE:
		SetWindowLongPtr(hwnd, 0, (LONG_PTR) ((LPCREATESTRUCT) lp)->lpCreateParams);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		if(wnd) wnd->handleMessage(hwnd, msg, wp, lp);
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	return 0;
}

#pragma managed

HINSTANCE getManagedInstanceHandle()
{
	Module^ module = ChromeHookCLR::MessageCallbackType::typeid->Module;
	return (HINSTANCE) Marshal::GetHINSTANCE(module).ToPointer();
}