using System.Windows;

namespace ChromeHookCLR
{
    public delegate void WindowMovedEventHandler(IChromeHook sender, Point position);

    public delegate void WindowSizeChangedEventHandler(IChromeHook sender, Size size);
}
