#pragma once

#include <Windows.h>
#include <tchar.h>

#include "Types.h"

#define MessageWindowClass (_T("ChromeHookCLR.MessageWindowClass"))

#define WindowPosChangedMessage (_T("ChromeHookCLR.Messages.WindowPosChanged"))
#define WindowSizeChangedMessage (_T("ChromeHookCLR.Messages.WindowSizeChanged"))

namespace ChromeHookCLR
{
	class MessageWindow
	{
	private:
		static bool initialized;

		// custom messages
		UINT windowPosChanged;
		UINT windowSizeChanged;

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