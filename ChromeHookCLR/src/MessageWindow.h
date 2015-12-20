#pragma once

#include <Windows.h>
#include <tchar.h>

#include "Types.h"

#define MessageWindowClass (_T("ChromeHookCLR.MessageWindowClass"))

#define WindowPosChangedMessage (_T("ChromeHookCLR.Messages.WindowPosChanged"))
#define WindowSizeChangedMessage (_T("ChromeHookCLR.Messages.WindowSizeChanged"))
#define WindowStateChangedMessage (_T("ChromeHookCLR.Messages.WindowStateChanged"))
#define WindowDestroyedMessage (_T("ChromeHookCLR.Messages.WindowDestroyed"))
#define WindowActivatedMessage (_T("ChromeHookCLR.Messages.WindowActivated"))

#define WindowNcLButtonDown (_T("ChromeHookCLR.Message.WindowNcLButtonDown"))

namespace ChromeHookCLR
{
	class MessageWindow
	{
	private:
		static bool initialized;

		// custom messages
		UINT windowPosChanged;
		UINT windowSizeChanged;
		UINT windowStateChanged;
		UINT windowDestroyed;
		UINT windowActivated;

		// my window handle
		HWND hwnd;

		// callback ptr
		NativeMessageCallbackType callback;

		void initialize();
		void registerClass();
		void registerMessage();

	public:
		MessageWindow();

		void createWindow();
		void close();
		void setCallback(NativeMessageCallbackType cb);
		void handleMessage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	};
}