﻿using System;

namespace ChromeHookCLR
{
    public interface IChromeHook
    {
        IntPtr Handle { get; }

        event WindowMovedEventHandler WindowMoved;
        event WindowSizeChangedEventHandler SizeChanged;
    }
}