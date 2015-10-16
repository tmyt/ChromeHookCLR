#pragma once

#include <windows.h>

namespace ChromeHookCLR
{
	public ref class ChromeHookService : public ChromeHookCLR::IChromeHookService
	{
	public:
		virtual ~ChromeHookService();

		virtual ChromeHookCLR::IChromeHook^ Register(System::IntPtr hwnd);
	};

	public ref class ChromeHookClient : public ChromeHookCLR::IChromeHook
	{
	private:
		HWND handle;

	public:
		ChromeHookClient(HWND hwnd) : handle(hwnd) { }
		virtual ~ChromeHookClient();

		virtual property System::IntPtr Handle {
			System::IntPtr get() { return System::IntPtr(handle); }
		}

		virtual event ChromeHookCLR::WindowMovedEventHandler^ WindowMoved;
		virtual event ChromeHookCLR::WindowSizeChangedEventHandler^ SizeChanged;

	internal:
		void OnWindowMoved(int x, int y);
		void OnWindowSizeChanged(int w, int h);
	};
}