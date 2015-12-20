using System;

namespace ChromeHookCLR
{
    public interface IChromeHookService
    {
        uint PseudoNcLButtonDownMessage { get; }

        IChromeHook Register(IntPtr hwnd);
    }
}
