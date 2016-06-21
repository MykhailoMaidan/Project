#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <winsock2.h>
#include <qdebug.h>


class ClientSocket
{
private:
    SOCKADDR_IN ClientAddr;
    WSADATA wsadata_client;

public:
    ClientSocket();
    void InitializeClient();
    void ConnectClient_to_Server();
    SOCKET SocketClient;
};

#endif // CLIENTSOCKET_H
