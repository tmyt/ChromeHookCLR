#include "stdafx.h"

#include "ChromeHookService.h"

#include <windows.h>

using namespace System;
using namespace ChromeHookCLR;

unsigned int g_ref = 0;

/*
 * ChromeHookService
 */

ChromeHookService::~ChromeHookService()
{
	if(!g_ref) { /* TODO: Stop hook */ }
}

IChromeHook^ ChromeHookService::Register(IntPtr hwnd)
{
	if (!g_ref) { /* TODO: Start hook */ }
	g_ref++;
	ChromeHookClient^ client = gcnew ChromeHookClient((HWND) hwnd.ToPointer());
	registeredWindows[(intptr_t)hwnd.ToPointer()] = client;
	return client;
}

void ChromeHookService::Unregister(HWND hwnd)
{
	g_ref--;
	if (!g_ref) { /* TODO: Stop hook */ }
	registeredWindows->erase((intptr_t)hwnd);
}

void ChromeHookService::HandleMessage(MessageType type, intptr_t hwnd, intptr_t arg)
{
	ChromeHookClient^ client = registeredWindows[hwnd];
	if (!client) return;
	switch (type)
	{
	case MessageType::Moved:
		client->OnWindowMoved(LOWORD(arg), HIWORD(arg));
		break;
	case MessageType::Size:
		client->OnWindowSizeChanged(LOWORD(arg), HIWORD(arg));
		break;
	}
}

/*
* ChromeHookClient (implementation of IChromeHook)
*/

ChromeHookClient::~ChromeHookClient()
{
	ChromeHookService::Unregister(handle);
}

void ChromeHookClient::OnWindowMoved(int x, int y)
{
	WindowMoved(this, System::Windows::Point(x, y));
}

void ChromeHookClient::OnWindowSizeChanged(int w, int h)
{
	SizeChanged(this, System::Windows::Size(w, h));
}