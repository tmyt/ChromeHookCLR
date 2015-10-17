using System;

namespace ChromeHookCLR
{
    public interface IChromeHookService : IDisposable
    {
        IChromeHook Register(IntPtr hwnd);
    }
}
