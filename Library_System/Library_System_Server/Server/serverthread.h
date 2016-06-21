#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include "socketserver.h"
#include <winsock2.h>

#include <QThread>



class ServerThread : public QThread
{
private:
    SocketServer* sockTread;
public:
    ServerThread(SocketServer * obj);
    void run();
};

#endif // SERVERTHREAD_H
