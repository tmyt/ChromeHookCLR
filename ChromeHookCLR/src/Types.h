#pragma once

#include <Windows.h>

namespace ChromeHookCLR
{
	enum class MessageType : int
	{
		Moved,
		Size
	};

#ifdef __cplusplus_cli
	delegate void MessageCallbackType(MessageType, intptr_t, intptr_t);
#endif

	typedef void(__stdcall *NativeMessageCallbackType)(MessageType, intptr_t, intptr_t);
}
