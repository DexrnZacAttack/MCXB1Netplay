#include "pch.h"
#include "SocketOutputStreamLocal.h"
#include <thread>

SOCKET SocketOutputStreamLocal::wSocket;

// maybe should be char** instead of int64_t**?
void SocketOutputStreamLocal::write(SocketOutputStreamLocal* self, int64_t** data, int32_t param_2, uint32_t size)
{
    //LOGW(data);
    send(wSocket, reinterpret_cast<char*>(*data), size, 0);
    // uncomment this to write to the socket
    //uint64_t* ass = SocketOutputStreamLocal_write(self, data, param_2, size);
    //return ass;
}

// TODO: Maybe WinSock class?
void SocketOutputStreamLocal::connectToServer() {
    try {
        // MIGHT NEED TO BE UDP, NEED TO VERIFY
        WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

        if (result != 0)
            throw std::runtime_error(std::to_string(result));

        wSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        // bind port found in appxmanifest
        addr.sin_port = htons(8700);
        // local address that forwards packets back to my local machine
        // loopback doesn't seem to work for me.
        // builders will either need to change this or have the same setup
        addr.sin_addr.s_addr = inet_addr("10.0.1.0");

        u_long mode = 1;
        ioctlsocket(wSocket, FIONBIO, &mode);

        LOGW(L"Connecting to ", addr.sin_addr.s_addr, ":", addr.sin_port);

        result = connect(wSocket, (struct sockaddr*)&addr, sizeof(addr));

        if (result == SOCKET_ERROR) {
            int error = WSAGetLastError();

            if (error == WSAEWOULDBLOCK) {
                fd_set writeFds;
                FD_ZERO(&writeFds);
                FD_SET(wSocket, &writeFds);

                struct timeval timeout;
                timeout.tv_sec = 5;  
                timeout.tv_usec = 0;

                // we need to read somehow but not yet.
                result = select(0, nullptr, &writeFds, nullptr, &timeout);
                if (result > 0) {
                    LOGW(L"Connected");
                } else if (result == 0) {
                    closesocket(wSocket);
                    WSACleanup();
                    throw std::runtime_error("TIMEOUT");
                } else {
                    closesocket(wSocket);
                    WSACleanup();
                    throw std::runtime_error(std::to_string(WSAGetLastError()));
                }
            }
            else {
                closesocket(wSocket);
                WSACleanup();
                throw std::runtime_error(std::to_string(error));
            }
        }
        else {
            LOGW(L"Connected");
        }
    }
    catch (const std::runtime_error& e) {
        // Ideally, we should send packet 255 on error.
        LOGW(e.what());
    }
    catch (const std::exception& e) {
        LOGW(e.what());
    }
}
