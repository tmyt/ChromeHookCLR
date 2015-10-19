using System;

namespace ChromeHookCLR
{
    public interface IChromeHookService
    {
        IChromeHook Register(IntPtr hwnd);
    }
}
