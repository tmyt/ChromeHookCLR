using System.Windows;

namespace ChromeHookCLR
{
    public delegate void WindowMovedEventHandler(IChromeHook sender, Point position);

    public delegate void WindowSizeChangedEventHandler(IChromeHook sender, Size size);

    public delegate void WindowStateChangedEventHandler(IChromeHook sender, int state);

    public delegate void WindowClosedEventHandler(IChromeHook sender);

    public delegate void WindowActivatedEventHandler(IChromeHook sender);

    public delegate void WindowDeactivatedEventHandler(IChromeHook sender);
}
