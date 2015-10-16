#include "stdafx.h"

#include "ChromeHookService.h"

#include <windows.h>

#define WINDOW_CLASS _T("ChromeHookCLR.MessageHandlerClass")

using namespace System;
using namespace ChromeHookCLR;

unsigned int g_ref = 0;

/*
 * ChromeHookService
 */

ChromeHookService::~ChromeHookService()
{

}

IChromeHook^ ChromeHookService::Register(IntPtr hwnd)
{
	if(!g_ref) { /* TODO: Start hook */ }
	g_ref++;
	return gcnew ChromeHookClient((HWND)hwnd.ToPointer());
}

/*
* ChromeHookClient (implementation of IChromeHook)
*/

ChromeHookClient::~ChromeHookClient()
{
	g_ref--;
}

void ChromeHookClient::OnWindowMoved(int x, int y)
{
	WindowMoved(this, System::Windows::Point(x, y));
}

void ChromeHookClient::OnWindowSizeChanged(int w, int h)
{
	SizeChanged(this, System::Windows::Size(w, h));
}