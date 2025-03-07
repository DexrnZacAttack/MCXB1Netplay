#pragma once
#include <Psapi.h>
#include <iostream>
#include <cstdio>
#include <cstdint>
#include "Util/Logger.h"
#include "Util/HookHelper.h"

class Socket {
public:
    static void Initialise(Socket* self, struct ServerConnection* connection);
};

CREATE_FUNC(Socket_Initialise, 0x1404c2850, void, Socket* self, struct ServerConnection* connection);
