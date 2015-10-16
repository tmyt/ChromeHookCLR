using System;
using System.IO;
using System.Reflection;

namespace ChromeHookCLR
{
    public static class ServiceFactory
    {

        private static string DllName32 = "ChromeHookCLR32.dll";
        private static string DllName64 = "ChromeHookCLR64.dll";

        private static string GetPlatformDllName()
        {
            var dir = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location) + "\\";
            return dir + (!Environment.Is64BitProcess ? DllName32 : DllName64);
        }

        public static IChromeHookService CreateInstance()
        {
            var asm = Assembly.LoadFile(GetPlatformDllName());
            var type = asm.GetType("ChromeHookCLR.ChromeHookService");
            return (IChromeHookService)Activator.CreateInstance(type);
        }
    }
}
