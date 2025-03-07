#include "pch.h"
#include "Socket.h"
#include <thread>
#include "SocketOutputStreamLocal.h"

void Socket::Initialise(Socket* self, struct ServerConnection* connection) {
	LOGW(L"Socket Init");
	Socket_Initialise(self, connection);
	// start the connection thread thing (threading asduhgjashdfshiukjasdf)
	std::thread(&SocketOutputStreamLocal::connectToServer).detach();
}
