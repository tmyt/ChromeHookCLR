using System;

namespace ChromeHookCLR
{
    public interface IChromeHook : IDisposable
    {
        IntPtr Handle { get; }

        event WindowMovedEventHandler WindowMoved;
        event WindowSizeChangedEventHandler SizeChanged;
        event WindowStateChangedEventHandler StateChanged;
        event WindowActivatedEventHandler Activated;
        event WindowDeactivatedEventHandler Deactivated;
        event WindowClosedEventHandler Closed;
    }
}
