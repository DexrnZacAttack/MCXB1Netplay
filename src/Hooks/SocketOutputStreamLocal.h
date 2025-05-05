#pragma once
#include <Psapi.h>
#include <iostream>
#include <cstdio>
#include <cstdint>
#include "Util/Logger.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Util/HookHelper.h"
//#include <winrt/Windows.Networking.Sockets.h>
//#include <winrt/Windows.Networking.h>
//#include <winrt/Windows.Foundation.h>
//#include <winrt/Windows.UI.Core.h>
//#include <winrt/base.h>
#include "OutputStream.h"

class SocketOutputStreamLocal : OutputStream {	
private:
	uint64_t unk;
public:
  	static SOCKET wSocket;

	// may actually still be int64_t*, I just changed it since it seemed like the return value was never used.
	static void write(SocketOutputStreamLocal* self, int64_t** param_1, int32_t param_2, uint32_t param_3);

	static void connectToServer();
};

CREATE_FUNC(SocketOutputStreamLocal_write, 0x14055d780, void, SocketOutputStreamLocal* self, int64_t** param_1,
            int32_t param_2, uint32_t param_3);

