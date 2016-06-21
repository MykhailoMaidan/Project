#include "serverthread.h"

ServerThread::ServerThread(SocketServer* obj)
{
   sockTread = obj;
}

void ServerThread::run()
{
    sockTread->AcceptSocket();
}
