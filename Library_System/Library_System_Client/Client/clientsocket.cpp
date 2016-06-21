#include "clientsocket.h"
#include <qdebug.h>

ClientSocket::ClientSocket()
{

}

void ClientSocket::InitializeClient() // initialize client socket
{
    if(WSAStartup(MAKEWORD(2,2), &wsadata_client)<0)
    {
        qDebug() << "Initialize client error...";
    }
   if((SocketClient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
   {
       qDebug() << "Socket error...";
   }
   ClientAddr.sin_family = AF_INET;
   ClientAddr.sin_port = htons(7777);
   ClientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
}

void ClientSocket::ConnectClient_to_Server() // connect client socket
{
    int sizeaddr = sizeof(ClientAddr);
    if(connect(SocketClient,(struct sockaddr*)&ClientAddr, sizeaddr)<0)
    {
        qDebug() << "Connect error...";
    }

}

