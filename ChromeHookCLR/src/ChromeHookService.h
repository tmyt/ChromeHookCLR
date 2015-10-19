#pragma once

#include <windows.h>
#include <cliext\map>

#include "Types.h"

#define PtrForDelegate(_delegate) \
	(System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_delegate).ToPointer())

namespace ChromeHookCLR
{
	ref class ChromeHookClient;

	public ref class ChromeHookService : public ChromeHookCLR::IChromeHookService
	{
	private:
		// native bridges
		static cliext::map<intptr_t, ChromeHookClient^>^ registeredWindows
			= gcnew cliext::map<intptr_t, ChromeHookClient^>();
		static MessageCallbackType^ callbackDelegate
			= gcnew MessageCallbackType(HandleMessage);

		// message handler
		static void HandleMessage(MessageType type, intptr_t hwnd, intptr_t arg);

	public:
		virtual ChromeHookCLR::IChromeHook^ Register(System::IntPtr hwnd);

	internal:
		// native fnptr
		static NativeMessageCallbackType callbackPtr
			= reinterpret_cast<NativeMessageCallbackType>(PtrForDelegate(callbackDelegate));
		// unregister window
		static void Unregister(HWND hwnd);
	};

	public ref class ChromeHookClient : public ChromeHookCLR::IChromeHook
	{
	private:
		HWND handle;
		int prevWindowState;

	public:
		ChromeHookClient(HWND hwnd) : handle(hwnd), prevWindowState(0) { }
		virtual ~ChromeHookClient();

		virtual property System::IntPtr Handle {
			System::IntPtr get() { return System::IntPtr(handle); }
		}

		virtual event ChromeHookCLR::WindowMovedEventHandler^ WindowMoved;
		virtual event ChromeHookCLR::WindowSizeChangedEventHandler^ SizeChanged;
		virtual event ChromeHookCLR::WindowStateChangedEventHandler^ StateChanged;
		virtual event ChromeHookCLR::WindowActivatedEventHandler^ Activated;
		virtual event ChromeHookCLR::WindowDeactivatedEventHandler^ Deactivated;
		virtual event ChromeHookCLR::WindowClosedEventHandler^ Closed;

	internal:
		void OnWindowMoved(int x, int y);
		void OnWindowSizeChanged(int w, int h);
		void OnWindowStateChanged(int state);
		void OnActivated(bool state);
		void OnWindowClosed();
	};
}